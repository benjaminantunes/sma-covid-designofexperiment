// global_rng.h
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#define norm 2.328306549295728e-10
#define m1   4294967087.0
#define m2   4294944443.0
#define a12     1403580.0
#define a13n     810728.0
#define a21      527612.0
#define a23n    1370589.0


class RandomGenerator {
public:
    RandomGenerator(int);  // Constructor to initialize RNG and counter
    double genrand_real1();  // Method to draw a random number
    unsigned int genrand_int32();
    double uniform(double, double);

private:
    double s10;
    double s11;
    double s12;
    double s20;
    double s21;
    double s22;
    unsigned long long global_counter;
};



#endif

