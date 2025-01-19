#include <stdio.h>
#include <pthread.h>

__thread int thread_specific_value; // Thread-local storage

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;
    thread_specific_value = thread_id * 10;
    printf("Thread %d: thread_specific_value = %d\n", thread_id, thread_specific_value);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
