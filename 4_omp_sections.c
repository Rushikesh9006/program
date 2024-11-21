#include <stdio.h>
#include <omp.h>

#define SIZE 10

void vec_add(int A[], int B[], int C[], int length)
{
        int i ;
        for(i=0 ; i < length ; i++)
        {
                C[i] = A[i] + B[i] ;
        }
}

void vec_mul(int A[], int B[], int D[], int length)
{
        int i ;
        for(i=0 ; i < length ; i++)
        {
                D[i] = A[i] * B[i] ;
        }
}

int main()
{
        int i ;
	int A[SIZE], B[SIZE], C[SIZE], D[SIZE] ;

        for(i=0 ; i < SIZE ; i++) 
	{ 
		A[i] = 4 ; B[i] = 4 ; C[i] = 0 ; D[i] = 0 ;
	}
	
	
        #pragma omp parallel
        {
			int ID = omp_get_thread_num() ;

                #pragma omp sections
                {
                        #pragma omp section
			{
                        	vec_add(A, B, C, SIZE) ;
							printf("Vec_add Thread [%d]\n", ID) ;
			}	
                        #pragma omp section
                        {
				vec_mul(A, B, D, SIZE) ;
				printf("Thread [%d]\n", ID) ;
			}
                }
        }

        for(i=0 ; i < SIZE ; i++) 
	{ 
		printf("[%d] ", C[i]) ; 
	}
        printf("\n") ;
        for(i=0 ; i < SIZE ; i++) 
	{ 
		printf("[%d] ", D[i]) ; 
	}
        printf("\n") ;

        return 0 ;
}

