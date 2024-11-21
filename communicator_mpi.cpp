# include <cstdlib>
# include <ctime>
# include <iostream>
# include <mpi.h>

using namespace std;
//This cpp program cab be compiled as follows
//mpic++ -o a.out communicator_mpi.cpp
//mpirun -np 4 ./a.out
int main ( int argc, char *argv[] );
void timestamp ( );

int main ( int argc, char *argv[] )
{
  MPI_Comm even_comm_id;
  MPI_Group even_group_id;
  int even_id;
  int even_id_sum;
  int even_p;
  int *even_rank;
  int i;
  int id;
  int ierr;
  int j;
  MPI_Comm odd_comm_id;
  MPI_Group odd_group_id;
  int odd_id;
  int odd_id_sum;
  int odd_p;
  int *odd_rank;
  int p;
  MPI_Group world_group_id;

ierr = MPI_Init ( &argc, &argv );

  if ( ierr != 0 )
  {
    cout << "\n";
    cout << "COMMUNICATOR_MPI - Fatal error!";
    cout << "  MPI_Init returned nonzero ierr.\n";
    exit ( 1 );
  }
ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
if ( id == 0 ) 
  {
    timestamp ( );
    cout << "\n";
    cout << "COMMUNICATOR_MPI - Master process:\n";
    cout << "  C++/MPI version\n";
    cout << "  An MPI example program.\n";
    cout << "\n";
    cout << "  The number of processes is " << p << "\n";
    cout << "\n";
  }
cout << "  Process " << id << " says 'Hello, world!'\n";
MPI_Comm_group ( MPI_COMM_WORLD, &world_group_id );
 even_p = ( p + 1 ) / 2;
  even_rank = new int[even_p];
  j = 0;
  for ( i = 0; i < p; i = i + 2 )
  {
    even_rank[j] = i;
    j = j + 1;
  }
  MPI_Group_incl ( world_group_id, even_p, even_rank, &even_group_id );

  MPI_Comm_create ( MPI_COMM_WORLD, even_group_id, &even_comm_id );
odd_p = p / 2;
  odd_rank = new int[odd_p];
  j = 0;
  for ( i = 1; i < p; i = i + 2 )
  {
    odd_rank[j] = i;
    j = j + 1;
  }
  MPI_Group_incl ( world_group_id, odd_p, odd_rank, &odd_group_id );

  MPI_Comm_create ( MPI_COMM_WORLD, odd_group_id, &odd_comm_id );

if ( id % 2 == 0 )
  {
    ierr = MPI_Comm_rank ( even_comm_id, &even_id );
    odd_id = -1;
  }
  else
  {
    ierr = MPI_Comm_rank ( odd_comm_id,  &odd_id );
    even_id = -1;
  }

if ( even_id != -1 )
  {
    MPI_Reduce ( &id, &even_id_sum, 1, MPI_INT, MPI_SUM, 0, even_comm_id );
  }
  if ( even_id == 0 )
  {
    cout << "  Number of processes in even communicator = " << even_p << "\n";
    cout << "  Sum of global ID's in even communicator  = " << even_id_sum << "\n";
  }
if ( odd_id != -1 )
  {
    MPI_Reduce ( &id, &odd_id_sum,  1, MPI_INT, MPI_SUM, 0, odd_comm_id );
  }
  if ( odd_id == 0 )
  {
    cout << "  Number of processes in odd communicator  = " << odd_p  << "\n";
    cout << "  Sum of global ID's in odd communicator   = " << odd_id_sum << "\n";
  }

ierr = MPI_Finalize ( );
if ( id == 0 )
  {
    cout << "\n";
    cout << "COMMUNICATOR_MPI:\n";
    cout << "  Normal end of execution.\n";
    cout << "\n";
    timestamp ( );
  }
  return 0;
}

void timestamp ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  std::cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}



