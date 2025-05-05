#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define TAG 0
#define MAIN 0
#define SIZE  10

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

void subtract_array(int *array){
	for(int a = 0 ;a < SIZE;a++){
		array[a] -= 1;
	}
}

int main(int argc, char *argv[]){
	int size,rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if(rank == MAIN){
		int vector[SIZE];
		for(int dest = 1; dest < size; dest++){
			fill_array(vector, dest*23);
			MPI_Send(vector, SIZE, MPI_INT, dest, TAG,MPI_COMM_WORLD);
			printf("Enviado o array para o rank %d com os valores\n",dest);
			print_array(vector);

			MPI_Recv(vector,SIZE,MPI_INT,dest,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Recebido o array do rank %d com os valores\n",dest);
			print_array(vector);
			printf("=\n");
		}
	}else{
		int vector[SIZE];
		MPI_Recv(vector, SIZE, MPI_INT, MAIN,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		subtract_array(vector);
		MPI_Send(vector,SIZE,MPI_INT,MAIN, TAG,MPI_COMM_WORLD);
	
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}
