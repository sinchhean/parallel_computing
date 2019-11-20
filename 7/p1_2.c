#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_NP 128

double f(double a) {
  return (4.0 / (1.0 + a*a));
}

int main(int argc,char *argv[]) {
  int n, id, np, i;
  double PI25DT = 3.141592653589793238462643;
  double startwtime, endwtime;
  double h, sum, allsum[MAX_NP], x, mypi;
  
  int s[MAX_NP], e[MAX_NP];
  
  if (argc == 1) n = 1000;
  else n = atoi(argv[1])*1000;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;

  startwtime = MPI_Wtime();

  if(id == 0){
    h = 1.0/(double)n;
    for(i=0;i<np;i++){
      s[i] = (n/np)*i;
      e[i] = (n/np)*(i+1) + (i+1 == np? n % np : 0);
    }
  }
  MPI_Bcast(&h, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(s, np, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(e, np, MPI_INT, 0, MPI_COMM_WORLD);
  sum = 0.0;

  // main loop
  for (i = s[id]; i < e[id]; i++) {
    x = h*((double)i - 0.5);
    sum += f(x);
  }
  printf("sum[%d]=%.16f\n",id,sum);
  MPI_Gather(&sum, 1, MPI_DOUBLE, allsum, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  if(id == 0){
    for(i=1;i<np;i++){
      sum = sum + allsum[i];
    }
    mypi = h*sum;
    endwtime = MPI_Wtime();
    printf("pi is approximately %.16f, Error is %.16f\n", mypi, fabs(mypi - PI25DT)/PI25DT);
    printf("wall clock time = %f\n", endwtime-startwtime);   
  }

  MPI_Finalize();
  return 0;
}

