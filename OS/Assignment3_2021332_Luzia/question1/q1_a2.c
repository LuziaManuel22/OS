#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

sem_t forks[NUM_FORKS];

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);

    while (1) {
        printf("Philosopher %d is thinking...\n", philosopher_id);
        sleep(1);

        // Acquire both forks
        sem_wait(&forks[philosopher_id]);
        sem_wait(&forks[(philosopher_id + 1) % NUM_FORKS]);

        printf("Philosopher %d is eating...\n", philosopher_id);
        sleep(1);

        // Release both forks
        sem_post(&forks[philosopher_id]);
        sem_post(&forks[(philosopher_id + 1) % NUM_FORKS]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize the forks
    for (int i = 0; i < NUM_FORKS; i++) {
        sem_init(&forks[i], 0, 1);
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

    // Destroy the forks
    for (int i = 0; i < NUM_FORKS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
