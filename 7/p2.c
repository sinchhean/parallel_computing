#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float f(float a) {
  return (4.0 / (1.0 + a*a));
}

int main(int argc,char *argv[]) {
  int n, id, np, i;
  double PI25DT = 3.141592653589793238462643;
  double startwtime, endwtime;
  float h, sum, x, mypi;
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
    for(i=np-1;i>0;i--){
      MPI_Send(&h, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
      s = (n/np)*i;
      e = (n/np)*(i+1) + (i+1 == np? n % np : 0);
      MPI_Send(&s,1,MPI_INT,i,1,MPI_COMM_WORLD);
      MPI_Send(&e,1,MPI_INT,i,2,MPI_COMM_WORLD);
    }
    /* Calculate s and e indexes for id=0 itself */
    s = (n/np)*id;
    e = (n/np)*(id+1) + (id+1 == np? n % np : 0);
  }else{
    MPI_Recv(&h, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD,&status);
    MPI_Recv(&s, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,&status);
    MPI_Recv(&e, 1, MPI_INT, 0, 2, MPI_COMM_WORLD,&status);
  }
  
  sum = 0.0;

  // main loop
  for (i = s; i < e; i++) {
    x = h*((float)i - 0.5);
    sum += f(x);
  }
  if(id != 0){
    MPI_Send(&sum, 1, MPI_FLOAT, 0, 4, MPI_COMM_WORLD);
  }else{
    float subsum;
    for(i=1;i<np;i++){
      MPI_Recv(&subsum, 1, MPI_FLOAT, i, 4, MPI_COMM_WORLD,&status);
      sum = sum + subsum;
    }
    printf("final sum = %.16f\n",sum);
    mypi = h*sum;
    endwtime = MPI_Wtime();
    printf("pi is approximately %.16f, Error is %.16f\n", mypi, fabs(mypi - PI25DT)/PI25DT);
    printf("wall clock time = %f\n", endwtime-startwtime);   
  }

  MPI_Finalize();
  return 0;
}

