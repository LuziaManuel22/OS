#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

sem_t forks[NUM_FORKS];
sem_t sauce_bowls[2];

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);

    while (1) {
        printf("Philosopher %d is thinking...\n", philosopher_id);
        sleep(1);

        // Acquire a fork and a sauce bowl
        sem_wait(&forks[philosopher_id]);
        sem_wait(&forks[(philosopher_id + 1) % NUM_FORKS]);
        sem_wait(&sauce_bowls[philosopher_id % 2]);

        printf("Philosopher %d is eating...\n", philosopher_id);
        sleep(1);

        // Release the fork and the sauce bowl
        sem_post(&forks[philosopher_id]);
        sem_post(&forks[(philosopher_id + 1) % NUM_FORKS]);
        sem_post(&sauce_bowls[philosopher_id % 2]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize the forks and sauce bowls
    for (int i = 0; i < NUM_FORKS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    for (int i = 0; i < 2; i++) {
        sem_init(&sauce_bowls[i], 0, 1);
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

    // Destroy the forks and sauce bowls
    for (int i = 0; i < NUM_FORKS; i++) {
        sem_destroy(&forks[i]);
    }
    for (int i = 0; i < 2; i++) {
        sem_destroy(&sauce_bowls[i]);
    }

    return 0;
}