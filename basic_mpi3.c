/*                                                          */
/*   .............CIRCULAR SHIFT TEST...................... */

/*   Objective   : Overhead measurment using circular shift */
/*                 collective communication                 */

/*   Input       : n number of processors and size of data  */

/*   Description : In this operation, processor i sends a   */
/*	           m-byte message to processor i+1,         */
/*                 and processor n-1 sends m-bytes back to  */
/*                 processor 0.                             */

/* MPI-LIBRARY   : Blocking send and recv is used           */

/*   Output      : overhead measurment                      */

/* Necessary Condition : Number of processors should be     */
/*               Multiple of Two                            */

/* Note : One can change "#if 0" and "#endif" for various   */
/*        Message size. One can chang the constant SIZE for */
/*        large data size                                   */



#include "mpi.h"
#include <sys/time.h>

#define PE_SIZE  8
#define FALSE  0
#define TRUE  1
#define SIZE (1024*89000)

  char  send_buffer[SIZE], recv_buffer[SIZE];

  int iproc, Found,
      ProcessorTable[PE_SIZE] = {2, 4, 6, 8, 12, 16, 24, 32};

main(int argc, char **argv)
{
  int j, MyRank, Numprocs;
  int Iterations;
  int Source, Destination;
  
  struct timeval TimeValue_Start;
  struct timeval TimeValue_Final;

  struct timezone TimeZone_Start;
  struct timezone TimeZone_Final;

  long time_start,time_end,time_overhead;
  long i, length, Maximum_Message_Size;

  MPI_Status status;

  Iterations = 15000; /* no. of ierations */

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &MyRank );
  MPI_Comm_size( MPI_COMM_WORLD, &Numprocs );

  for(iproc = 0 ; iproc < PE_SIZE ; iproc++) {
     if(ProcessorTable[iproc] == Numprocs) {
	Found = TRUE;
	break;
     }
     else 
	Found = FALSE;
  }

  if(!Found) {
     printf(" Input is wrong. Number of processors needed is 2/4/6/8/12/16/24/32 ... \n");
     MPI_Finalize();
     exit(-1);
  }

  for(length = 0; length<SIZE; length++)
  {
    send_buffer[length] = (char)(length % 256);
    recv_buffer[length] =' ';
  }

  /* for message size - 1 byte to 1001 bytes */
   if(MyRank == 0) printf(" \n For message size - 1 Byte to 1001 Bytes \n");
  Maximum_Message_Size = 10001; 
 
  for(i = 1; i <= Maximum_Message_Size; i=i+100)
  {
     length = i;
     MPI_Barrier(MPI_COMM_WORLD);

     gettimeofday(&TimeValue_Start, &TimeZone_Start);

     for(j = 1; j <= Iterations; j++) 
     {
       /* Forward Direction Loop ........*/
       if(MyRank == 0) 
       {
 	  Destination = MyRank + 1;
          MPI_Send(send_buffer,length,MPI_BYTE,Destination,1,MPI_COMM_WORLD);
       } 
       else
       {
   	  if(MyRank != Numprocs-1) 
	  {
	     Source = MyRank - 1;
             MPI_Recv(recv_buffer,length,MPI_BYTE,Source,1, MPI_COMM_WORLD, &status);

	     Destination = MyRank + 1;
             MPI_Send(send_buffer,length,MPI_BYTE,Destination,1,MPI_COMM_WORLD);
	  }
	  else
	  {
	      Source = MyRank - 1;
              MPI_Recv(recv_buffer,length,MPI_BYTE,Source,1, MPI_COMM_WORLD, &status);
	  }
       } /* If loop for Backwrd Direction is done */

       /* Backward Direction */
       if(MyRank == Numprocs -1) 
       {
 	 Destination = 0;
         MPI_Send(send_buffer,length,MPI_BYTE,Destination,1,MPI_COMM_WORLD);
       }
      else
       {
          if(MyRank == 0) 
 	  {
	   Source = Numprocs - 1 ;
           MPI_Recv(recv_buffer,length,MPI_BYTE,Source ,1, MPI_COMM_WORLD, &status);
          }    /* For Backwrd Direction to zero */
       }
    }  /* loop for iterations */

    gettimeofday(&TimeValue_Final, &TimeZone_Final);

    /* Check for Corruption of Message */
    for(j = 0; j<length; j++)
    {
         if(send_buffer[j] != recv_buffer[j])
         printf("\n[%d] Message corrupted at %d \n",length,j);
     }
 
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end   = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;

    time_overhead = (time_end - time_start)/(float) (Iterations);

    if(MyRank ==  0) 
      printf("\n Size[bytes] %4d, Total_time[us] %ld", i,time_overhead);
  }        /* loop for First Data Size */

  MPI_Finalize();
}


