#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_mutex_t forks[NUM_FORKS];
pthread_cond_t cond_var[NUM_FORKS];

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);

    while (1) {
        printf("Philosopher %d is thinking...\n", philosopher_id);
        sleep(1);

        pthread_mutex_lock(&forks[philosopher_id]);
        pthread_mutex_lock(&forks[(philosopher_id + 1) % NUM_FORKS]);

        printf("Philosopher %d is eating...\n", philosopher_id);
        sleep(1);

        pthread_cond_signal(&cond_var[philosopher_id]);
        pthread_cond_signal(&cond_var[(philosopher_id + 1) % NUM_FORKS]);
        pthread_mutex_unlock(&forks[philosopher_id]);
        pthread_mutex_unlock(&forks[(philosopher_id + 1) % NUM_FORKS]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize the forks and condition variables
    for (int i = 0; i < NUM_FORKS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&cond_var[i], NULL);
    }

    // Create the philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for the philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the forks and condition variables
    for (int i = 0; i < NUM_FORKS; i++) {
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&cond_var[i]);
    }

    return 0;
}
