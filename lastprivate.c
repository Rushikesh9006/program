#include<stdio.h>

#include<omp.h>

int main(void)
{
	int x = 44 , i , tid ; 
	
	#pragma omp parallel for num_threads(5) private(i , tid) lastprivate(x) schedule(dynamic)
	for(i=0 ; i<20 ; i++)
	{
		x = i;
			 
		printf("tid = %d , iteration = %d , x = %d\n" , omp_get_thread_num() , i, x);

	}
	 
	printf("x=%d\n" , x);

}
