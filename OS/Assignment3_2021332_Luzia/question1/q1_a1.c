#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_mutex_t forks[NUM_FORKS];

void *philosopher(void *id) {
  int philosopher_id = *((int*)id);
  int left_fork = philosopher_id;
  int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

  while (1) {
    // Think
    printf("Philosopher %d is thinking\n", philosopher_id);
    sleep(1);

    // Pick up left fork
    pthread_mutex_lock(&forks[left_fork]);
    printf("Philosopher %d picked up left fork %d\n", philosopher_id, left_fork);

    // Pick up right fork
    pthread_mutex_lock(&forks[right_fork]);
    printf("Philosopher %d picked up right fork %d\n", philosopher_id, right_fork);

    // Eat
    printf("Philosopher %d is eating\n", philosopher_id);
    sleep(1);

    // Put down right fork
    pthread_mutex_unlock(&forks[right_fork]);
    printf("Philosopher %d put down right fork %d\n", philosopher_id, right_fork);

    // Put down left fork
    pthread_mutex_unlock(&forks[left_fork]);
    printf("Philosopher %d put down left fork %d\n", philosopher_id, left_fork);
  }
}

int main() {
  pthread_t philosophers[NUM_PHILOSOPHERS];
  int ids[NUM_PHILOSOPHERS];

  // Initialize mutexes for forks
  for (int i = 0; i < NUM_FORKS; i++) {
    pthread_mutex_init(&forks[i], NULL);
  }

  // Create philosopher threads
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }

  // Wait for philosopher threads to finish
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}