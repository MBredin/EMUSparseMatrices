#!/bin/sh
#SBATCH --job-name emuLargeMatrix
#SBATCH --output test.out
#SBATCH --nodes 4
#SBATCH --mail-user ammarwa@nmsu.edu
#SBATCH --mail-type BEGIN 
#SBATCH --mail-type END
#SBATCH --mail-type FAIL
#SBATCH --get-user-env

module load python-dev/3.6
export PATH=$PATH:/home/ammarwa/emuB
emu-cc /home/ammarwa/emuBenchmarking/EMUSparseMatrices/emuArch/coo/ammar.c -o /home/ammarwa/emuBenchmarking/EMUSparseMatrices/emuArch/coo/test.mwx
emusim.x /home/ammarwa/emuBenchmarking/EMUSparseMatrices/emuArch/coo/test.mwx 2
