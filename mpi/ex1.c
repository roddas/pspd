#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mpi.h>

#define MAIN 0

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int rank,size, counter = 0;
	int vector [15] = {5313,24,7863,74,7705,86,27,38,49,910,6181,912,1963,184,195}; 
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank == MAIN){
		for(int a = 1 ; a < size; a++){
			int num = vector[counter];
			MPI_Send(&num,1, MPI_INT, a ,0,MPI_COMM_WORLD);
			//printf("Processo main enviou %d para o processo branch\n",num);
			counter++;
		}
	}else{
		int received;
		MPI_Recv(&received,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Processo branch com o ranking %d, recebeu o número %d\n",rank,received);
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}
