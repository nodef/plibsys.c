#define PLIBSYS_IMPLEMENTATION
#include "plibsys.h"
#include <stdio.h>

static PMutex *mutex;
static PCondVariable *cond;
static int shared_data = 0;

void *producer(void *data) {
    p_mutex_lock(mutex);
    shared_data = 42;
    printf("Producer: Data produced\n");
    p_cond_variable_signal(cond);
    p_mutex_unlock(mutex);
    return NULL;
}

void *consumer(void *data) {
    p_mutex_lock(mutex);
    while (shared_data == 0) {
        p_cond_variable_wait(cond, mutex);
    }
    printf("Consumer: Data consumed: %d\n", shared_data);
    p_mutex_unlock(mutex);
    return NULL;
}

int main() {
    p_libsys_init();

    mutex = p_mutex_new();
    cond = p_cond_variable_new();

    PUThread *prod_thread = p_uthread_create(producer, NULL, TRUE, "ProducerThread");
    PUThread *cons_thread = p_uthread_create(consumer, NULL, TRUE, "ConsumerThread");

    p_uthread_join(prod_thread);
    p_uthread_join(cons_thread);

    p_uthread_unref(prod_thread);
    p_uthread_unref(cons_thread);

    p_mutex_free(mutex);
    p_cond_variable_free(cond);

    p_libsys_shutdown();
    return 0;
}
