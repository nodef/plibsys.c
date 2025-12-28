#include <linmath.h>
#include <stdio.h>


int main() {
  vec4 a = {1.0f, 2.0f, 3.0f, 1.0f};
  vec4 b = {4.0f, 5.0f, 6.0f, 1.0f};
  vec4 result;

  // Vector addition
  vec4_add(result, a, b);
  printf("Vector addition: (%f, %f, %f, %f)\n", result[0], result[1], result[2],
         result[3]);

  // Vector scaling
  vec4_scale(result, a, 2.0f);
  printf("Vector scaling: (%f, %f, %f, %f)\n", result[0], result[1], result[2],
         result[3]);

  // Homogeneous transformation example
  vec4 c = {1.0f, 2.0f, 3.0f, 0.0f}; // Direction vector
  vec4_scale(result, c, 3.0f);
  printf("Homogeneous transformation (scaled direction): (%f, %f, %f, %f)\n",
         result[0], result[1], result[2], result[3]);

  return 0;
}
