#include<stdio.h>
#include<omp.h>

void test(int val);
int main(void)
{
	test(0);
	test(4);

}

void test(int val)
{
	#pragma omp parallel num_threads(4) if(val)
	{
		printf("hello world from thread = %d of %d , val=%d\n" , omp_get_thread_num() , omp_get_num_threads(), val);



	 }

	
}
