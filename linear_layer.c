#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



float random_float(){
   return (float) rand() / (float) RAND_MAX;
}

float random_normal(){
   float U_1 = random_float();
   float U_2 = random_float();

   float Z_0 = sqrtf(-2 * logf(U_1)) * cosf(2 * M_PI * U_2);
   return Z_0;
}


int main() {
   srand(time(0));
}
