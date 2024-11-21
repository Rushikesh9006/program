#include<stdio.h>
#include<omp.h>

int main(void)
{
	int count=0 , dec=20;

	#pragma omp parallel num_threads(20)
	{
		#pragma omp atomic
		count++;
		#pragma omp atomic
		dec--; 

	} 

	printf("count = %d\n" , count);
	printf("dec=%d\n" , dec);

}
