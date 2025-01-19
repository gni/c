#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

FILE *log_file;
pthread_mutex_t log_mutex;

void init_logger(const char *filename) {
    log_file = fopen(filename, "a");
    if (!log_file) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_init(&log_mutex, NULL);
}

void log_message(const char *message) {
    pthread_mutex_lock(&log_mutex);
    fprintf(log_file, "%s\n", message);
    fflush(log_file);
    pthread_mutex_unlock(&log_mutex);
}

void close_logger() {
    pthread_mutex_destroy(&log_mutex);
    fclose(log_file);
}

void *worker(void *arg) {
    log_message((char *)arg);
    return NULL;
}

int main() {
    init_logger("app.log");

    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        char message[50];
        sprintf(message, "Thread %d logging...", i + 1);
        pthread_create(&threads[i], NULL, worker, strdup(message));
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    close_logger();
    return 0;
}
