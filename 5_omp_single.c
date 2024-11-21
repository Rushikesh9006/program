#include <stdio.h>
#include <omp.h>

int main() 
{
	int i ;
	#pragma omp parallel num_threads(4) 
	{
		int ID = omp_get_thread_num() ;
		#pragma omp single // #pragma omp master
		{
			//single specifies that a section of code should be executed by single thread and not necessarily the master thread 
			printf("Threads Single [%d]\n", ID) ;
			for(i =0 ; i < 10000000 ; i++) { /* Long Wait */ }
		}

		printf("Threads [%d]\n", ID) ;
	}

	return 0 ;
}
