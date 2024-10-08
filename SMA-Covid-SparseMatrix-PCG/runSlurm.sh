#!/bin/bash
#================= OPTIONS (s'applique à chaque job du tableau) =========================
#SBATCH --ntasks=30
#SBATCH --cpus-per-task=1
#SBATCH --nodelist=node36
#SBATCH --mem-per-cpu=10000
#SBATCH --output=simulationParis-30repli-PCG-sparseMatrix
#========================== TASKS ================================
make clean
make
./replicationSimulation.sh 30 configVaccin configDpt75
