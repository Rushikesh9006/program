#include<stdio.h>
#include<omp.h>

int main(void)
{
	omp_set_num_threads(4);
	int i=0;	
	#pragma omp parallel 
	for(i=0;i<14;i++)
	{
		printf("thread %d is processing iteration %d\n",omp_get_thread_num(),i);
	}	
	return(0);
}
