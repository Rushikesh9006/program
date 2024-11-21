#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 100000000

void vecADD(int *X, int *Y, int *Z, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		Z[i]=X[i]+Y[i];
	}
}

//Using MPI and OpenMP
//
int main(int argc, char *argv[])
{
	int rank, size, flag;
	int *A, *B, *C;
	int strideLen, sIndex, lIndex;
	int *X, *Y, *Z;
	double startTime, endTime;
	int i;

	MPI_Init(&argc,&argv);
	MPI_Initialized(&flag);
	if(flag==0)
	{
		MPI_Init(&argc,&argv);
	}
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	//size of sub-Matrix
	strideLen=N/size;
	sIndex=rank*strideLen;
	lIndex=(rank+1)*strideLen-1;

	//Initialization	
	if(rank == 0)
	{
		A=(int *)malloc(sizeof(int)*N);
		B=(int *)malloc(sizeof(int)*N);
		C=(int *)malloc(sizeof(int)*N);
		for(i=0;i<N;i++)
		{
			A[i] = 1;
			B[i] = 2;
		}

	}
	X=(int *)malloc(sizeof(int)*strideLen);
	Y=(int *)malloc(sizeof(int)*strideLen);
	Z=(int *)malloc(sizeof(int)*strideLen);
	startTime=MPI_Wtime();
	//Scatter ec A to all processes
	MPI_Scatter(A,strideLen,MPI_INT,X,strideLen,MPI_INT,0,MPI_COMM_WORLD);
	//Scatter Vec B to all Processes	
	MPI_Scatter(B,strideLen,MPI_INT,Y,strideLen,MPI_INT,0,MPI_COMM_WORLD);
	//Perform MA
	vecADD(X,Y,Z, strideLen);
	MPI_Barrier(MPI_COMM_WORLD);
	//Gather the result from all processes
	MPI_Gather(Z,strideLen,MPI_INT,C,strideLen,MPI_INT,0,MPI_COMM_WORLD);
	endTime=MPI_Wtime();
	if(rank==0)
	{
		printf("\n Vec A:");
		for(i=N-10;i<N;i++)
		{
			printf("%d \t", A[i]);
		}
		printf("\n Vec B:");
                for(i=N-10;i<N;i++)
                {
                        printf("%d \t", B[i]);
                }
		printf("\n Execution Time %lf", endTime-startTime);
		printf("\n Vec C:");
		for(i=N-10;i<N;i++)
		{
			printf("%d \t", C[i]);
		}
		printf("\n");

	}
	
	MPI_Finalize();
	return 0 ;
}

