// global_rng.h
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include "philox.hpp"
class RandomGenerator {
public:
    RandomGenerator(int);  // Constructor to initialize RNG and counter
    double genrand_real1();  // Method to draw a random number
    unsigned int genrand_int32();
    double uniform(double, double);

private:
    typedef r123::Philox2x32 CBRNG;
    CBRNG rng;
    CBRNG::ctr_type  ctr;
    CBRNG::key_type key;
    CBRNG::ctr_type rand;
    unsigned long long global_counter;
};



#endif

