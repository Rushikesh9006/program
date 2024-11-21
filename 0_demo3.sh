#!/bin/bash
#SBATCH -J openmp
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
##SBATCH -w, --nodelist=cn001,cn091,cn092,cn093
#SBATCK --ntasks=1
##SBATCH --cpus-per-tasks=24
#SBATCH --time=01:00:00
#SBATCH --error=%J.err
#SBATCH --output=%J.out
#SBATCH --partition=standard
#SBATCH --exclusive

##compile line can be added
gcc -fopenmp 0_demo3.c -o demo3.out
./demo3.out
sleep 30
