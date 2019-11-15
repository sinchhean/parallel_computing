#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  int np, id;
  MPI_Init(&argc, &argv);

  //Query the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  //Query own ID
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  printf("Hello world from process %d (%d)\n",id,np);

  MPI_Finalize();
  return 0;
}
