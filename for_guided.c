#include <stdio.h>
#include <omp.h>

int main()
{

	int i ;

	omp_set_num_threads(4) ;
	#pragma omp parallel for schedule(guided, 4)
	for(i =0 ; i < 20 ; i++)
	{
		int ID = omp_get_thread_num() ;
		printf("Threads [%d] doing some task on i: %d\n", ID, i) ;
	}

	return 0; 
}
