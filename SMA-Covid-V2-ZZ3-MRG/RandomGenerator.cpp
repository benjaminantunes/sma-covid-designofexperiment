#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int seed){ 

    s10 = seed +1;
    s11 = seed +1;
    s12 = seed +1;
    s20 = seed +1;
    s21 = seed +1;
    s22 = seed +1;
}


double RandomGenerator::genrand_real1(){
   //return genrand_int32() * (1.0 / 4294967295.0);
   long k;
   double p1, p2;
   /* Component 1 */
   p1 = a12 * s11 - a13n * s10;
   k = p1 / m1;
   p1 -= k * m1;
   if (p1 < 0.0)
      p1 += m1;
   s10 = s11;
   s11 = s12;
   s12 = p1;

   /* Component 2 */
   p2 = a21 * s22 - a23n * s20;
   k = p2 / m2;
   p2 -= k * m2;
   if (p2 < 0.0)
      p2 += m2;
   s20 = s21;
   s21 = s22;
   s22 = p2;

   /* Combination */
   if (p1 <= p2)
      return ((p1 - p2 + m1) * norm);
   else
      return ((p1 - p2) * norm);

}



unsigned int RandomGenerator::genrand_int32(){

   return genrand_real1()*4294967295;
}

double RandomGenerator::uniform(double a, double b)
{
    return a + (b - a) * genrand_real1();
}
