#include <linmath.h>
#include <stdio.h>


int main() {
  mat4x4 identity, rotation, result;
  mat4x4_identity(identity);

  // Create a rotation matrix (90 degrees around Z-axis)
  mat4x4_rotate_Z(rotation, identity, 3.14159f / 2);

  // Multiply matrices
  mat4x4_mul(result, identity, rotation);

  // Print the resulting matrix
  printf("Resulting matrix:\n");
  for (int i = 0; i < 4; ++i) {
    printf("[%f, %f, %f, %f]\n", result[i][0], result[i][1], result[i][2],
           result[i][3]);
  }

  return 0;
}
