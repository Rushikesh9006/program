#include<stdio.h>
#include<omp.h>

int main(void)
{
	int a=125 , tid ;

	#pragma omp parallel num_threads(5) firstprivate(a) private(tid )
	{
		int tid = omp_get_thread_num();
		printf("after firstprivate operation : tid = %d and a=%d\n" , tid , a);
		
		#pragma omp barrier

		#pragma omp single copyprivate(a)
		{ 
			a = a*2;
			printf("in single block a =%d , tid = %d\n" , a , tid);
		}
		
		printf("after copyprivate a = %d and tid = %d\n" , a, tid );
	}


}
