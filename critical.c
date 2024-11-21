#include<stdio.h>
#include<omp.h>

#define size 200

int main(void)
{
	int a[size] , i , max ;
	
	for(i=0 ; i<size ; i++)
		a[i] = i+1;
	
	max = a[0] ;

	#pragma omp parallel for num_threads(20)
	for(i=0 ; i<size ; i++)
	{
		#pragma omp critical
		{
			if(a[i] > max) 
			max = a[i];
		}
	} 

	printf("max = %d\n" , max);
}
