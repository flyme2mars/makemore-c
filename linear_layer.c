#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Memory Allocation */
extern inline void *malloc_check(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed at %s:%d\n", file, line);
        fprintf(stderr, "Error details:\n");
        fprintf(stderr, "  File: %s\n", file);
        fprintf(stderr, "  Line: %d\n", line);
        fprintf(stderr, "  Size: %zu bytes\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

#define mallocCheck(size) malloc_check(size, __FILE__, __LINE__)


/* random_float gives a random floating point number between 0.0 and 1.0*/
float random_float(){
   return (float) rand() / (float) RAND_MAX;
}

/* random_normal gives a random floating point number from a normal distribution. This is achieved using Box–Muller transform*/
float random_normal(){
   float U_1 = random_float();
   float U_2 = random_float();

   // Box-Muller transform
   float Z_0 = sqrtf(-2 * logf(U_1)) * cosf(2 * M_PI * U_2);
   return Z_0;
}


/* rand_arr outputs an array of random floats between 0.0 and 1.0 from a uniform distribution */
float *rand_arr(int num){
   float *arr = (float*)mallocCheck(num * sizeof(float));
   for (int i = 0; i < num; i++) {
      arr[i] = random_float();
   }
   return arr;
}

/* randn_arr outputs an array of random floats from a normal distribution */
float *randn_arr(int num){
   float *arr = (float*)mallocCheck(num * sizeof(float));
   for (int i = 0; i < num; i++) {
      arr[i] = random_normal();
   }
   return arr;
}

float **initialize_weights(int fan_in, int fan_out){
   float **weights = (float **)mallocCheck(fan_out*sizeof(float *));
   for (int i=0; i < fan_out; i++){
      weights[i] = randn_arr(fan_in);
   }
   return weights;
}

float *initialize_bias(int fan_out) {
   float *bias = randn_arr(fan_out);
   return bias;
}

float dot_product(float *a, float *b, int len){
   float dp = 0;
   for(int i = 0; i < len; i++){
      dp += a[i] * b[i]; 
   }
   return dp;
}

float *linear_layer(int fan_in,int fan_out, float* x){
   float **weights = initialize_weights(fan_in, fan_out);
   float *bias = initialize_bias(fan_out);
   float *activations = (float *)mallocCheck(fan_out * sizeof(float));
   for (int i = 0; i < fan_out; i++){
      activations[i] = dot_product(x, weights[i], fan_in) + bias[i];
   }
   return activations;
}

void tan_h(float* a, int len){
   for (int i = 0; i < len; i++){
      a[i] = tanhf(a[i]);
   }
}

int main() {
   srand(time(0));
   float *x = randn_arr(20);
   float *activations = linear_layer(20, 10, x);
   for (int i = 0; i < 10; i++){
      printf("%f ", activations[i]);
   }
   printf("\n");
   tan_h(activations, 10);
   for (int i = 0; i < 10; i++){
      printf("%f ", activations[i]);
   }
   printf("\n");
}
