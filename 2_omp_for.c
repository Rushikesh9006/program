#include <stdio.h>

#include <omp.h>

int main()
{
        int i, SUM = 0 ;
        int thread_sum[8] ;

        omp_set_num_threads(8) ;

        #pragma omp parallel
        {
                int thread_id = omp_get_thread_num() ; 

                thread_sum[thread_id] = 0 ; 

                #pragma omp for
                for(i = 1 ; i <= 10; i++)
                {
                        thread_sum[thread_id] += i ;
			printf("For Loop Thread Sum %d\n", thread_sum[thread_id]) ;
                }

		#pragma omp master
		{
			printf("Master Thread sum %d\n", thread_sum[0]) ;
		}
				
        }

        for(i=0 ; i < 8 ; i++)
        {
                SUM += thread_sum[i] ;
        }

        printf("SUM : %d\n", SUM) ;
}

