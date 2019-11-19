#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double a) {
  return (4.0 / (1.0 + a*a));
}

int main(int argc,char *argv[]) {
  int n, id, np, i;
  double PI25DT = 3.141592653589793238462643;
  double startwtime, endwtime;
  double h, sum, x, mypi;
  int s, e;

  if (argc == 1) n = 1000;
  else n = atoi(argv[1])*1000;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;

  startwtime = MPI_Wtime();

  if(id == 0){
    h = 1.0/(double)n;
    for(i=1;i<np;i++){
      MPI_Send(&h, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    }
    for(i=np-1;i>=0;i--){
      s = (n/np)*i;
      e = (n/np)*(i+1) + (i+1 == np? n % np : 0);
      if(i != 0){
        MPI_Send(&s,1,MPI_INT,i,1,MPI_COMM_WORLD);
        MPI_Send(&e,1,MPI_INT,i,2,MPI_COMM_WORLD);
      }
    }
  }else{
    MPI_Recv(&h, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,&status);
    MPI_Recv(&s, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,&status);
    MPI_Recv(&e, 1, MPI_INT, 0, 2, MPI_COMM_WORLD,&status);
  }
  
  sum = 0.0;

  // main loop
  for (i = s; i < e; i++) {
    x = h*((double)i - 0.5);
    sum += f(x);
  }

  if(id != 0){
    MPI_Send(&sum, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD);
  }else{
    double subsum;
    for(i=1;i<np;i++){
      MPI_Recv(&subsum, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD,&status);
      sum = sum + subsum;
    }
    mypi = h*sum;
    endwtime = MPI_Wtime();
    printf("pi is approximately %.16f, Error is %.16f\n", mypi, fabs(mypi - PI25DT)/PI25DT);
    printf("wall clock time = %f\n", endwtime-startwtime);   
  }

  MPI_Finalize();
  return 0;
}

