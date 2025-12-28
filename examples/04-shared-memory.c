#define PLIBSYS_IMPLEMENTATION
#include "plibsys.h"
#include <stdio.h>
#include <string.h>

int main() {
    p_libsys_init();

    const char *key = "plibsys_shared_memory";
    const char *message = "Hello from shared memory!";

    PShm *shm = p_shm_new(key, strlen(message) + 1, P_SHM_ACCESS_READWRITE, NULL);
    if (shm == NULL) {
        printf("Failed to create shared memory\n");
        p_libsys_shutdown();
        return 1;
    }

    char *data = (char *)p_shm_get_address(shm);
    strcpy(data, message);

    printf("Written to shared memory: %s\n", data);

    p_shm_free(shm);
    p_libsys_shutdown();
    return 0;
}
