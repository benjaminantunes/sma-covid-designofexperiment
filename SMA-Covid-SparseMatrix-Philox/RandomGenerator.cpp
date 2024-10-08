#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int seed){ 

    ctr = {{0,0}};
    global_counter = 0;
    key = {{seed}};
}


double RandomGenerator::genrand_real1(){
   return genrand_int32() * (1.0 / 4294967295.0);

}



unsigned int RandomGenerator::genrand_int32(){
   rand = rng(ctr, key);
   global_counter++;
   ctr[0] = global_counter;
   //std::cout << "Number: " << rand[0] << std::endl;
   return rand[0];
}

double RandomGenerator::uniform(double a, double b)
{
    return a + (b - a) * genrand_real1();
}
