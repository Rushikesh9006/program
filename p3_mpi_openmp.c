#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#define N 10

//Using MPI and OpenMP
//
int main(int argc, char *argv[])
{
	int rank, size;
	int localSum, globalSum;
	int localMax, globalMax;
	int localMin, globalMin;

	int *gData=NULL;
	int *data=NULL;
	int sIndex;
	int i;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	data=(int *)malloc(sizeof(int)*N/size);

	if(rank == 0)
	{
		gData=(int *)malloc(sizeof(int)*N);
		for(i=0;i<N;i++)
		{ 
			gData[i] = i+1;
		}
	}
		MPI_Scatter(gData, N/size, MPI_INT,data, N/size, MPI_INT,0,MPI_COMM_WORLD);		

	localSum=data[0];
	localMax=data[0];

	#pragma omp parallel for reduction(+:localSum)
	for(i=1; i<N/size;i++)
	{
		localSum+=data[i];
	}

	for(i = 1;i<N/size;i++){
	{
		if(data[i]>localMax){ localMax=data[i];}
		if(data[i]<localMin){ localMin=data[i];}
	}

	MPI_Reduce(&localSum,&globalSum,1,MPI_INT,MPI_SUM,0, MPI_COMM_WORLD);
	MPI_Reduce(&localMax,&globalMax,1,MPI_INT,MPI_MAX,0, MPI_COMM_WORLD);
	MPI_Reduce(&localMin,&globalMin,1,MPI_INT,MPI_MIN,0, MPI_COMM_WORLD);

	if(rank==0)
		printf("\n Global sum is: %d \n Global Max is: %d\n Global Min is: %d\n", globalSum,globalMax,globalMin);

	MPI_Barrier(MPI_COMM_WORLD);
	for(i=0;i<N/size;i++)
	{
		printf(" %d-->%d  ", rank,data[i]);
	}
		
	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n %d rank local SUM is %d \n", rank,localSum);

	MPI_Finalize();
	return 0 ;
}
}
