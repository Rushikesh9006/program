#include<stdio.h>

#include<omp.h>

int x  , tid ;

#pragma omp threadprivate(x , tid)

int main(void)
{
	int i ;

	printf("first parallel region\n");

	#pragma omp parallel num_threads(5) private(i)
	{
		tid = omp_get_thread_num();
		x = 2*tid +1 ;
		printf("tid = %d , x = %d\n" , tid , x); 


	}
	
 	printf("second parallel region\n");

	#pragma omp parallel num_threads(5) private(i)
	{
		printf("tid = %d , x = %d\n", tid , x);

	} 
	
	printf("after copyin operation\n");

	#pragma omp parallel copyin(x) num_threads(5)
	{
		printf("tid = %d , x = %d\n" , tid , x);		 

	}
}
