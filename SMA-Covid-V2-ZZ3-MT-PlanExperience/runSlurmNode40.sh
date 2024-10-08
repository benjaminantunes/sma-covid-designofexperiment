#!/bin/bash
#================= OPTIONS (s'applique à chaque job du tableau) =========================
#SBATCH --ntasks=64
#SBATCH --cpus-per-task=1
#SBATCH --nodelist=node40
#SBATCH --partition=repro
#SBATCH --mem=0
#SBATCH --output=simulationParis-fullPlanExperienceNode40.out
#SBATCH --error=simulationParis-fullPlanExperienceNode40.err
#========================== TASKS ================================
make clean
make

replications=3
batch_size=20
counter=0

# Logging start time and environment
echo "Starting job at $(date)" > job.log
echo "Running on node: $(hostname)" >> job.log
echo "SLURM job ID: $SLURM_JOB_ID" >> job.log
echo "SLURM job name: $SLURM_JOB_NAME" >> job.log
echo "SLURM node list: $SLURM_NODELIST" >> job.log

# Loop over each configVaccin file
for i in $(seq 200 244); do
    # Pair each configVaccin file with each configDpt75 file
    for j in $(seq 1 5); do
        # Execute the simulation command in the background and log the output
        echo "Running ./replicationSimulation.sh $replications configVaccin_variant_${i}.txt configDpt75_variant_${j}.txt" >> job.log
        ./replicationSimulation.sh $replications configVaccin_variant_${i}.txt configDpt75_variant_${j}.txt >> job.log 2>> job.err &
        
        # Increment the counter
        ((counter++))

        # Check if we need to wait for processes to finish
        if [ $counter -eq $batch_size ]; then
            wait # Wait for all background processes to finish
            counter=0 # Reset counter
        fi
    done
done

# Wait for the last batch to complete, if any
wait

# Logging end time
echo "Job finished at $(date)" >> job.log

