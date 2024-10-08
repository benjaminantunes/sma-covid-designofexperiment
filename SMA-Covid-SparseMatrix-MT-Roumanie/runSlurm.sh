#!/bin/bash
#================= OPTIONS (s'applique à chaque job du tableau) =========================
#SBATCH --ntasks=30
#SBATCH --cpus-per-task=1
#SBATCH --mem=0
#SBATCH --nodelist=kephren
#SBATCH --partition=court
#SBATCH --output=simulationRoumanie-30repli-MT-fullmap
#SBATCH --profile=Memory
#========================== TASKS ================================
make clean
make
./replicationSimulation.sh 3 configVaccin configRoumanie

sacct --format=JobID,MaxRSS,Elapsed -j $SLURM_JOB_ID

# Collecte des informations sur la RAM maximale utilisée
max_ram=$(sstat -j $SLURM_JOB_ID --format=MaxRSS | tail -n 1)

echo "La RAM maximale utilisée par le job est de $max_ram"

