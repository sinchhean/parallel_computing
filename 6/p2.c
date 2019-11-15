#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int np, id;
  MPI_Init(&argc, &argv);

  //Query the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  //Query own ID
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  //printf("Hello world from process %d (%d)\n",id,np);
  int data = 0;
  if(id%2 == 0){
    data = 1;
  }else{
    data = 100;
  }

  int i = 0;
  for(i=0;i<np-1;i++){
    if(i != id){
      MPI_Send(&data, 1, MPI_INT, i, id, MPI_COMM_WORLD);
      
    }
  }
  for(i=0;i<np-1;i++){
    MPI_Status status;
    int data1;
    MPI_Recv(&data1,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
  }

  
  
  MPI_Finalize();
  //printf("final data is %d\n.",data);

  return 0;
}
