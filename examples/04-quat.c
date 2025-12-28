#include <linmath.h>
#include <stdio.h>


int main() {
  quat q1, q2, result;

  // Initialize quaternions
  quat_identity(q1);
  quat_rotate(q2, 3.14159f / 2,
              (vec3){0.0f, 0.0f, 1.0f}); // 90 degrees around Z-axis

  // Quaternion multiplication
  quat_mul(result, q1, q2);

  // Print the resulting quaternion
  printf("Resulting quaternion: (%f, %f, %f, %f)\n", result[0], result[1],
         result[2], result[3]);

  // Rotate a vector using the quaternion
  vec3 v = {1.0f, 0.0f, 0.0f};
  vec3 rotated_v;
  quat_mul_vec3(rotated_v, result, v);
  printf("Rotated vector: (%f, %f, %f)\n", rotated_v[0], rotated_v[1],
         rotated_v[2]);

  return 0;
}
