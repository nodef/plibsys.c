#define PLIBSYS_IMPLEMENTATION
#include "plibsys.h"
#include <stdio.h>

void *thread_function(void *data) {
    printf("Thread %d is running\n", *(int *)data);
    return NULL;
}

int main() {
    p_libsys_init();

    PUThread *threads[5];
    int thread_ids[5];

    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i + 1;
        threads[i] = p_uthread_create(thread_function, &thread_ids[i], TRUE, "Thread");
        if (threads[i] == NULL) {
            printf("Failed to create thread %d\n", i + 1);
        }
    }

    for (int i = 0; i < 5; i++) {
        if (threads[i] != NULL) {
            p_uthread_join(threads[i]);
            p_uthread_unref(threads[i]);
        }
    }

    p_libsys_shutdown();
    return 0;
}
