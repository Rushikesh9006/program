#include <stdio.h>
#include <omp.h>

#define SIZE 10

void fun1()
{
	printf("I am in fun1\n");
}

void fun2()
{
	printf("I am in fun2\n");
}

int main()
{

        #pragma omp parallel
        {
			int ID = omp_get_thread_num() ;

                #pragma omp sections
                {
                        #pragma omp section
			{
				//int ID = omp_get_thread_num(); //returns the unique thread ID
        		        printf("Hello my ID is %d\n", ID);
				fun1();
			}
			#pragma omp section
                        {
				printf("Hello my ID is %d\n", ID);
				fun2();
			}

                }
        }

        return 0 ;
}

