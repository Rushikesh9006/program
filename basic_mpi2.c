#include   <stdio.h>
#include   <mpi.h>
main(int argc, char *argv[])
{
   int rank;
	  int source,result,root;

	  /* run on 10 processors */

	  MPI_Init(&argc, &argv);
	  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	  root=3;
	  source=rank+1;
	  MPI_Barrier(MPI_COMM_WORLD);

	  MPI_Reduce(&source,&result,1,MPI_INT,MPI_PROD,root,MPI_COMM_WORLD);
	  if(rank==root) printf("P:%d MPI_PROD result is %d \n",rank,result);
			 
			 MPI_Finalize();
}
