#!/bin/bash

#SBATCH --mem=200G
#SBATCH --partition=court
#SBATCH --job-name=job
#SBATCH --output=job_%a.out
#SBATCH --nodelist=kephren
##SBATCH --exclusive
#SBATCH --array=38-42

# Exécution de la simulation

cd ..

config=$((SLURM_ARRAY_TASK_ID))

./replicationSimulation.sh 1 configToyEpidemicalContext ./generationConfigDepartement/configDpt$config
