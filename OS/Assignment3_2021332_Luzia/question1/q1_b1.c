#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5
#define NUM_SAUCE_BOWLS 2

// semaphores for each fork and sauce bowl
sem_t forks[NUM_FORKS];
sem_t sauce_bowls[NUM_SAUCE_BOWLS];

void* philosopher(void* arg) {
  int id = *((int*) arg);

  while (1) {
    // philosophers must request forks and sauce bowls in a strict order
    int left_fork = id;
    int right_fork = (id + 1) % NUM_FORKS;
    int sauce_bowl = id % NUM_SAUCE_BOWLS;

    // request left fork
    sem_wait(&forks[left_fork]);
    printf("Philosopher %d has taken fork %d\n", id, left_fork);

    // request right fork
    sem_wait(&forks[right_fork]);
    printf("Philosopher %d has taken fork %d\n", id, right_fork);

    // request sauce bowl
    sem_wait(&sauce_bowls[sauce_bowl]);
    printf("Philosopher %d has taken sauce bowl %d\n", id, sauce_bowl);

    // eat
    printf("Philosopher %d is eating\n", id);

    // release forks and sauce bowl
    sem_post(&forks[left_fork]);
    sem_post(&forks[right_fork]);
    sem_post(&sauce_bowls[sauce_bowl]);

    // think
    printf("Philosopher %d is thinking\n", id);
  }
}

int main() {
  // initialize semaphores
  for (int i = 0; i < NUM_FORKS; i++) {
    sem_init(&forks[i], 0, 1);
  }
  for (int i = 0; i < NUM_SAUCE_BOWLS; i++) {
    sem_init(&sauce_bowls[i], 0, 1);
  }

  // create philosopher threads
  pthread_t philosophers[NUM_PHILOSOPHERS];
  int ids[NUM_PHILOSOPHERS];
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }

  // wait for philosopher threads to finish
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}
