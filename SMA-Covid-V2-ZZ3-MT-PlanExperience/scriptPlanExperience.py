import itertools

# Define possible values for the variables
#1 - 3
#For defaultVariantHistoConta|| and histogrammeContamination|| and variantsHistoConta||
histogram_contamination_variants = [
    [0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.8, 0.6, 0.4, 0.2],
    [0.7, 0.8, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8, 0.7, 0.5, 0.3],
    [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.6, 0.4, 0.2, 0.1]
]

#2 - 3 
#For pourcentAsymptomatiqueVariants|| and pourcentAsymptomatique||
asymptomatic = [0.2, 0.5, 0.8]

#3 - 3
#For resistanceInfectionValuesByAge||
resistance_reinfection = [
   [0.999,0.999,0.999,0.999,0.99,0.90,0.80,0.70],
   [0.6,0.6,0.6,0.6,0.6,0.5,0.4,0.3],
   [0.3,0.3,0.3,0.3,0.3,0.2,0.1,0.1]
]

#4 - 3
#For maxResistanceInjectionValuesByAge|| and minResistanceInjectionValuesByAge||
max_resistance_vaccin = [
   [0.8,0.8,0.8,0.7,0.6,0.6,0.5,0.4],
   [0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9],
   [0.3,0.3,0.3,0.3,0.2,0.2,0.2,0.1]
]
min_resistance_vaccin = [
   [0.5,0.5,0.5,0.5,0.4,0.4,0.4,0.3],
   [0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8],
   [0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1]
]

#5 - 3
#For timelineVaccination||
timeline_vaccination = ["1,10","1,50","1,90"]

#6 - 5
#For nbDeplacementJour|| , inside the file configDpt75, instead of configVaccin.
nb_deplacement_jour = [1,5,10,20,30]

#Total combination : 3*3*3*3*3*5 = 1215
#There should be 243 configVaccin_variant_$i file and 5 configDpt75_variant_$i files.
#Then, i will need a bash script to run the 1215 combinations : ./replicationSimulation.sh 3 configVaccin_variant_$i configDpt75_variant_$i
# replications for each of the 1215 experiments, so around 4000 experiments. 

# Compute all combinations
all_combinations = list(itertools.product(
    histogram_contamination_variants,
    asymptomatic,
    resistance_reinfection,
    zip(max_resistance_vaccin, min_resistance_vaccin),  # Pair max and min resistances
    timeline_vaccination  # Add timelineVaccination to combinations
))

# Load the content of the original file
with open("configVaccin", "r") as file:
    content = file.readlines()

# Generate new files for each combination
for i, combo in enumerate(all_combinations):
    hc, a, rri, (mrv, mnrv), tv = combo
    new_content = []
    for line in content:
        if "defaultVariantHistoConta||" in line:
            new_content.append(f"defaultVariantHistoConta||{','.join(map(str, hc))}\n")
        elif "variantsHistoConta||" in line:
            new_content.append(f"variantsHistoConta||{','.join(map(str, hc))}\n")
        elif "histogrammeContamination||" in line:
            new_content.append(f"histogrammeContamination||{','.join(map(str, hc))}\n")
        elif "pourcentAsymptomatiqueVariants||" in line:
            new_content.append(f"pourcentAsymptomatiqueVariants||{a}\n")
        elif "pourcentAsymptomatique||" in line:
            new_content.append(f"pourcentAsymptomatique||{a}\n")
        # Add conditions for each additional parameter
        elif "resistanceInfectionValuesByAge||" in line:
            new_content.append(f"resistanceInfectionValuesByAge||{','.join(map(str, rri))}\n")
        elif "maxResistanceInjectionValuesByAge||" in line:
            new_content.append(f"maxResistanceInjectionValuesByAge||{','.join(map(str, mrv))}\n")
        elif "minResistanceInjectionValuesByAge||" in line:
            new_content.append(f"minResistanceInjectionValuesByAge||{','.join(map(str, mnrv))}\n")
        elif "timelineVaccination||" in line:
            new_content.append(f"timelineVaccination||{tv}\n")
        else:
            new_content.append(line)

    # Write the new configuration to a file
    with open(f"configVaccin_variant_{i+1}.txt", "w") as new_file:
        new_file.writelines(new_content)

# Load the content of the original file
with open("configDpt75", "r") as file:
    content = file.readlines()

j = 0   
for i in nb_deplacement_jour:
    j += 1
    new_content = []
    for line in content:
        if "nbDeplacementJour||" in line:
            new_content.append(f"nbDeplacementJour||{i}\n")
        else:
            new_content.append(line)
            
    # Write the new configuration to a file
    with open(f"configDpt75_variant_{j}.txt", "w") as new_file:
        new_file.writelines(new_content)

