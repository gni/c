#include <stdio.h>
#include <pthread.h>

void *print_message(void *arg) {
    char *message = (char *)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, print_message, "Thread 1: Hello!");
    pthread_create(&thread2, NULL, print_message, "Thread 2: World!");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
