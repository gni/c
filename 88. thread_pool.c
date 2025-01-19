#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 4
#define QUEUE_SIZE 10

typedef struct {
    void (*function)(void *);
    void *arg;
} Task;

typedef struct {
    Task tasks[QUEUE_SIZE];
    int front, rear, count;
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t threads[MAX_THREADS];
    int stop;
} ThreadPool;

ThreadPool *create_pool() {
    ThreadPool *pool = malloc(sizeof(ThreadPool));
    pool->front = pool->rear = pool->count = pool->stop = 0;
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->notify, NULL);
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&pool->threads[i], NULL, (void *(*)(void *))worker, pool);
    }
    return pool;
}

void *worker(ThreadPool *pool) {
    while (1) {
        pthread_mutex_lock(&pool->lock);
        while (pool->count == 0 && !pool->stop) {
            pthread_cond_wait(&pool->notify, &pool->lock);
        }
        if (pool->stop) {
            pthread_mutex_unlock(&pool->lock);
            break;
        }
        Task task = pool->tasks[pool->front];
        pool->front = (pool->front + 1) % QUEUE_SIZE;
        pool->count--;
        pthread_mutex_unlock(&pool->lock);

        task.function(task.arg);
    }
    return NULL;
}

void submit_task(ThreadPool *pool, void (*function)(void *), void *arg) {
    pthread_mutex_lock(&pool->lock);
    pool->tasks[pool->rear] = (Task){function, arg};
    pool->rear = (pool->rear + 1) % QUEUE_SIZE;
    pool->count++;
    pthread_cond_signal(&pool->notify);
    pthread_mutex_unlock(&pool->lock);
}

void destroy_pool(ThreadPool *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->notify);
    pthread_mutex_unlock(&pool->lock);

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->notify);
    free(pool);
}

void print_message(void *arg) {
    printf("Task: %s\n", (char *)arg);
}

int main() {
    ThreadPool *pool = create_pool();

    submit_task(pool, print_message, "Hello");
    submit_task(pool, print_message, "World");

    sleep(1);
    destroy_pool(pool);
    return 0;
}
