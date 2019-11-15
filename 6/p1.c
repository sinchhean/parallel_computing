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


  if(id != 0){
    int data = id;
    MPI_Send(&data,1,MPI_INT,0,id,MPI_COMM_WORLD);
  }else{
  int i = 0;
  for(i = 0; i < np-1; i++){
    MPI_Status status;
    int data1;
    MPI_Recv(&data1,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    printf("Receive %d from %d\n",data1*data1,data1);
  }
  }
  
  MPI_Finalize();

  return 0;
}
