#include <linmath.h>
#include <stdio.h>


int main() {
  vec3 a = {1.0f, 2.0f, 3.0f};
  vec3 b = {4.0f, 5.0f, 6.0f};
  vec3 result;

  // Vector addition
  vec3_add(result, a, b);
  printf("Vector addition: (%f, %f, %f)\n", result[0], result[1], result[2]);

  // Vector subtraction
  vec3_sub(result, a, b);
  printf("Vector subtraction: (%f, %f, %f)\n", result[0], result[1], result[2]);

  // Dot product
  float dot = vec3_mul_inner(a, b);
  printf("Dot product: %f\n", dot);

  // Cross product
  vec3_mul_cross(result, a, b);
  printf("Cross product: (%f, %f, %f)\n", result[0], result[1], result[2]);

  return 0;
}
