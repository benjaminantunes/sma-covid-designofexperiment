# SMA-Epidemiology-C++
### Owner of this repository : Benjamin Antunes, PhD student at Limos.
### Working with Pr. David Hill (LIMOS) aka Benny.

This repository contains an epidemiological model, done initially for Covid19.

Articles : \
https://uca.hal.science/hal-03768175/file/SMA-Covid-RR%20Hill-Antunes%20v20.pdf  (deprecated)\
https://uca.hal.science/hal-03739929/document (deprecated)

This model is developed in C++ for performance. It is parallelized in SPMD (several simulations run simultaneously, Single Program Multiple Data). You will therefore be limited by your number of computing cores (and your RAM).
To run the toyCase example on the notebook, you do not need much resources.


## Prerequisites : 
- Linux machine

# Reproducibility :
Guix is a package manager, built for reproducibility. (https://guix.gnu.org/en/)
We used this tool to make our project reproducible.

To ensure reproducibility, we provided an example of toyCase. You can easily repeat this experiment to check for bitwise reproducibility.

Then, you will be able to draw your own experiments.

First, you will need to clone/download this repository, and open a terminal.

## 1 - Guix : 
If you have Guix installed on your machine or cluster, you will easily be able to re-create the same environment as us, and will then be able to use our model.

You should use : *guix time-machine -C channels.scm -- shell -C -m manifest.scm --preserve='^DISPLAY$' --share=/tmp*\
This command will create a virtual environment where you can work isolated from your system.\
To open the jupyter notebook, use the command : *jupyter notebook&*\
This will give you an URL to connect to the notebook.\
Open icecat by using the command: *icecat*\
And copy the URL inside (you need to activate Javascript in your browser)

To manually run the experiment, you can do : *make clean* then *make*\
and : *bash replicationSimulation 1 configToyEpidemicalContext configToyState*\
This will run 1 replication of the epidemy configuration contains in "configToyEpidemicalContext" and geographical configuration of "configToyState". You will obtain a result file, which you can analyse with the jupyter notebook.


## 2 - Apptainer (Singularity)
The second option we offer to ensure reproducibility is Apptainer.\
You can use the following command inside the folder : *apptainer shell wspss1pn96fwdqjjpb3758cz01p5812k-bash-python-python-numpy-python-pandas-squashfs-pack.gz.squashfs*

This will start a container with needed packages. You can then do the same procedure as with Guix.

## 3 - Nothing
You do not want/cannot use Guix or Apptainer. You will then have to get everything you need by yourself.\
You need : 
 - Python 3 : sudo apt-get install python3
 - Jupyter : sudo apt-get install jupyter
 - gcc : sudo apt-get install gcc (if gcc version is to old, this will not work)

 And also some Python libs like pandas, csv, scipy, statistics, ... You can probably install them with pip install. 

## 4 - Docker and Tarball
You will also have the possibility to use Docker or a Tarball. I did not experiment this myself, but they are respectively contained in : 6xsjpxijir5rnsns25gp52j3g2i3ndna-coreutils-bash-icecat-gcc-toolchain-docker-pack.tar.gz  and  zmjkyrsdwk7s47n55l2bprp0qsvf2wmi-coreutils-bash-icecat-gcc-toolchain-tarball-pack.tar.gz 

You can find some documentation about the usage on : https://guix.gnu.org/tr/blog/2018/tarballs-the-ultimate-container-image-format/



## File Description:

The .cpp and .hpp files correspond to the code of the model. You don't need to modify them (but you can).

The makefile allows you to compile the project correctly.

The "mts-0000-0999" folder contains "mts000M00X" files that are statuses of the Mersenne Twister pseudo-random number generator. They are spaced by 2 billion draws. For example, 30 files allow you to run 30 independent replications of simulations, which should use a maximum of 2 billion random numbers. To learn more about parallelizing code that uses pseudo-random number generators, please refer to this article: HILL D. PASSERAT-PALMBACH J. MAZEL C., TRAORE, M.K., "Distribution of Random Streams for Simulation Practitioners," Concurrency and Computation: Practice and Experience, June 2013, Vol. 25, Issue 10, pp. 1427-1442.\
Available here: https://hal.archives-ouvertes.fr/hal-01099203 

The bash file "ReplicationSimulation.sh" allows you to launch simulations.

The Jupyter notebook "SMA Covid.ipynb" allows you to easily launch your experiments and retrieve your results.

The configuration files "configDpt" and "configVaccin" allow you to define configurations for cities/countries/territories and set various disease parameters as well as the implemented health measures.

## Getting Started:

To get started with the model, simply launch the Jupyter notebook using the command "jupyter notebook" in a terminal or any other means of your choice.

You can execute all the cells.

The command !make will compile the program.\
The command !./replicationSimulation 1 configToyEpidemicalContext configToyState needs to be modified for your own experiment

You can use your own city and measurement configuration files by following the existing format. Initially, you can try the model with the existing configurations and compare your results with those already obtained to test repeatability. If your results are different, contact us at benjamin.antunes@uca.fr (we can investigate the causes of non-repeatability).
This command may take some time. It will run the C++ code with N simulations for each geographical zone you have chosen with your configuration file.
For example, the line:
./replicationSimulation 5 configNoVaccine configToyState configTexas
Will launch 5 replications of the simulation on ToyState with configNoVaccine and 5 replications on Texas config file.
There will be a total of 10 replications (10 processes launched in parallel).


The operation is as follows: The code will generate log files for each simulation you launched. The last cell will use these logs to generate statistics and figures for each simulation and store them in the directory where the notebook was launched. You can then draw your own conclusions about the impact of health measures on the epidemic, for example.

Note: You need to calibrate the model according to the cities you are using. The model is not generic.
It is possible to scale it to a department/country level, but this will require more computational power and, especially, memory.

## Les paramètres : 

### Geographical file : 
- size: Population size.
- nbHumain: Number of humans.
- nbMalade: Number of infected individuals.
- nbIteration: Number of iterations.
- nbPlaceHospital: Number of hospital beds.
- nbPlaceReanimation: Number of intensive care beds.
- nbDeplacementJour: Number of daily movements (for infected people to contamine others).
- probasCumulativesTrancheAge: Cumulative age group probabilities.
- nbHopitaux: Number of hospitals. (delete this ?)
- tailleHopitauxMetreCarre: Hospital sizes in square meters. (delete this ?)
- facteurTailleHopitaux: Hospital size factor. (delete this ?)
- nbSalleDeSport: Number of sports halls.
- nbBoiteDeNuit: Number of nightclubs.
- nbMagasin: Number of shops.
- nbRestaurant: Number of restaurants.
- tailleVille: City sizes.
- nbHabitant: Number of inhabitants by city.
- coordonneeX: X coordinates of each city.
- coordonneeY: Y coordinates of each city.

### Epidemiological file : 
- nbVariants: Number of variants.
- defaultVariantHistoConta: Default histogram of variant contamination rates.
- variantsHistoConta: Histogram of variant contamination rates.
- dureeVariants: Duration of variants.
- pourcentAsymptomatiqueVariants: Percentage of asymptomatic cases for each variant.
- tableTauxHospitalisationByAgeVariants: Hospitalization rates by age for each variant.
- tauxMortRea: Mortality rate in intensive care units.
- isVaccin: Flag indicating whether vaccination is enabled.
- r0: Basic reproduction number. (unused)
- resistanceInfectionValuesByAge: Resistance to infection by age.
- maxResistanceInjectionValuesByAge: Maximum resistance to infection given by injection by age.
- minResistanceInjectionValuesByAge: Minimum resistance to infection given by injection by age.
- tableTauxHospitalisationByAge: Hospitalization rates by age.
- histogrammeContamination: Histogram of contamination rates.
- pourcentAsymptomatique: Percentage of asymptomatic cases.
- tauxDeChanceDeMourirHospitalFull: Mortality rate when full hospitals.
- timelineVaccination: Timeline for vaccination.
- timelineVaccinationRappel: Timeline for vaccination booster shots.
- tauxDeProtectionHospVaccinByAge: Hospitalization protection rates by age for vaccinated individuals.
- tauxDeProtectionReaVaccinByAge: Intensive care protection rates by age for vaccinated individuals.
- tauxDeProtectionHospVaccinRappelByAge: Hospitalization protection rates by age for vaccinated individuals (booster shots).
- tauxDeProtectionReaVaccinRappelByAge: Intensive care protection rates by age for vaccinated individuals (booster shots).
- tauxDeProtectionHospInfectionByAge: Hospitalization protection rates by age for infected individuals.
- tauxDeProtectionReaInfectionByAge: Intensive care protection rates by age for infected individuals.
- isMedicament: Flag indicating whether medication is enabled.
- timelineMedicament: Timeline for medication.
- tauxProtectionReaMedicament: Medication protection rate in intensive care units.
- isMasqueTissu: Flag indicating whether cloth masks are enabled.
- timelineMasqueTissu: Timeline for cloth masks.
- tauxProctectionMasqueTissu: Cloth mask protection rate.
- isMasqueChir: Flag indicating whether surgical masks are enabled.
- timelineMasqueChir: Timeline for surgical masks.
- tauxProtectionMasqueChir: Surgical mask protection rate.
- isMasqueFFP2: Flag indicating whether FFP2 masks are enabled.
- timelineMasqueFFP2: Timeline for FFP2 masks.
- tauxProtectionMasqueFFP2: FFP2 mask protection rate.
- isConfinement: Flag indicating whether confinement is enabled.
- timelineConfinement: Timeline for confinement.
- nbDeplacementReductionConfinement: Number of reduced movements during confinement.
- nbLimiteDistanceMaxConfinement: Maximum distance limit during confinement.
- isDeplacementLimites: Flag indicating whether movement restrictions are enabled.
- timelineDeplacementLimites: Timeline for movement restrictions.
- nbDistanceMax: Maximum distance limit for movement.
- isGelHydroalcolique: Flag indicating whether hand sanitizers are enabled.
- timelineGelHydroalcolique: Timeline for hand sanitizers.
- tauxProtectionTransmissionGelHydro: Hand sanitizer transmission protection rate.
- isTestCovid: Flag indicating whether COVID testing is enabled. (unused)
- tauxDeDivisionAsymptomatique: Percentage of asymptomatic cases that self-isolate. (unused)
- isCouvreFeu: Flag indicating whether curfew is enabled.
- timelineCouvreFeu: Timeline for curfew.
- nbDeplacementReductionCouvreFeu: Number of reduced movements during curfew.
- nbSuperContaminateur: Number of super-spreaders.
- rayonSuperContaminateur: Radius of super-spreaders' impact.
- tauxAugmentationContaminationHopitaux: Rate of increased hospital contamination.
- tauxContaminationHopitaux: Hospital contamination rate.
- tauxAugmentationContaminationGym: Rate of increased gym contamination.
- tauxContaminationGym: Gym contamination rate.
- tauxAugmentationContaminationClub: Rate of increased club contamination.
- tauxContaminationClub: Club contamination rate.
- tauxAugmentationContaminationShop: Rate of increased shop contamination.
- tauxContaminationShop: Shop contamination rate.
- tauxAugmentationContaminationRestaurant: Rate of increased restaurant contamination.
- tauxContaminationRestaurant: Restaurant contamination rate.
- tauxObesitePopulation: Obesity rate in the population.
- tauxAugmentationReaObesite: Rate of increased intensive care admissions due to obesity.
- tauxAugmentationHospObesite: Rate of increased hospital admissions due to obesity.
- tauxDiabetePopulation: Diabetes rate in the population.
- tauxAugmentationReaDiabete: Rate of increased intensive care admissions due to diabetes.
- tauxAugmentationHospDiabete: Rate of increased hospital admissions due to diabetes.

## Expected Ouput : 
The folder expectedOutput contains the expected output of the toy case. You can use diff command to verify numerical reproducibility.
