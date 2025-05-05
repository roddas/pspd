#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define SIZE 10
#define TAG 0
#define MAIN 0

void fill_array(int *array, int BUFF){
	for(int a = 0; a < SIZE;a++){
		array[a] = BUFF;
	}
}
void print_array(int *array){
	for(int a = 0; a < SIZE - 1;a++){
		printf("%d, ",array[a]);
	}
	printf("%d\n",array[SIZE - 1]);
}

int main(int argc, char **argv){
	int rank,size;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0){
		int vector[SIZE];
		for(int dest = 1; dest < size; dest++){
			fill_array(vector,23*dest);

			MPI_Send(vector,SIZE,MPI_INT,dest,TAG,MPI_COMM_WORLD);
		}

	}else{
		int vector[SIZE];
		MPI_Recv(vector,SIZE,MPI_INT,MAIN,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Ranking %d recebeu o seguinte vetor:\n",rank);
		print_array(vector);
	}

	MPI_Finalize();
	return EXIT_SUCCESS;
}
