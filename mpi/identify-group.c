#include<stdio.h>
#include<unistd.h>
#include<mpi.h>

int main(int argc, char **argv){
	MPI_Init(&argc,&argv);
	int my_rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("PID %d tem rank %d\n",getpid(), my_rank);
	MPI_Finalize();
	return 0;
}
