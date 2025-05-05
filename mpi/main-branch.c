#include<stdio.h>
#include<mpi.h>
#include<unistd.h>

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int rank,size;
	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0) { // Iam the main
		for(int i = 1; i < size;i++){
			int n = i * 10;
			MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Main: Enviei %d para o rank %d\n",n,i);
		}
	}
	else{ 
		// Iam the branch
		int received;
		MPI_Recv(&received, 1, MPI_INT,0,0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	MPI_Finalize();
	return 0;
}

