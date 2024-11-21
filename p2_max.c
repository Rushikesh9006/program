#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10

//Maxima of 40 numbers using 4 processes

int main(int argc, char *argv[])
{
	int rank, size;
	int localMax, globalMax;
	int data[N];
	int i;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	srand(rank*2);
	for(i=0;i<N;i++)
	{
		data[i]= rand()%1000;
	}

	//Find local Maximum
	localMax=data[0];
	for(i=1;i<N;i++)
	{
		if(data[i] > localMax)
		{
			localMax=data[i];
		}
	}

	//MPI_Reduce
	MPI_Reduce(&localMax, &globalMax, 1, MPI_INT, MPI_MAX,0,MPI_COMM_WORLD);
	
	if(rank == 0)
	{
		printf("\n Global Maximum is: %d \n", globalMax);
		for(i=0;i<N;i++)
		{ printf("%d\n", data[i]);}
	}
		for(i=0;i<N;i++)
                { 
			printf("%d --> %d , ", rank,data[i]);
		}

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n %d rank local maximum is %d \n", rank,localMax);	

	MPI_Finalize();
	return 0 ;
}
