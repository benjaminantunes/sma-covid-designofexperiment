#!/bin/bash
#================= OPTIONS (s'applique à chaque job du tableau) =========================
#SBATCH --ntasks=64
#SBATCH --cpus-per-task=1
#SBATCH --nodelist=node35
#SBATCH --mem=0
#SBATCH --output=simulationParis-fullPlanExperienceNode35
#========================== TASKS ================================
make clean
make


replications=3
batch_size=20
counter=0


# Loop over each configVaccin file
for i in $(seq 150 300); do
    # Pair each configVaccin file with each configDpt75 file
    for j in $(seq 1 5); do
        # Execute the simulation command in the background
        ./replicationSimulation.sh $replications configVaccin_variant_${i}.txt configDpt75_variant_${j}.txt &
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

