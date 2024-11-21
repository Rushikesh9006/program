#include <stdio.h>

#include <omp.h>


int main()
{
        int i ;

        omp_set_num_threads(8) ;
        #pragma omp parallel num_threads(4)
        {
                printf("Hello from Classroom\n") ;
        }

        return 0 ;
}

