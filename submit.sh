#!/bin/sh
##SBATCH --job_name=mpi_job
#SATH --time=00:10:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=4
#SBATCH --output=%j.out
#SBATCH --error=%j.err

mpirun -np 4 ./ex3
