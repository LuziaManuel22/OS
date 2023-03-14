#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define LENGTH 50  // Length of each string
#define N 50  // Number of strings
#define GROUP_SIZE 5  // Number of strings sent at a time
#define SHM_KEY 1234  // Key for shared memory
#define TIMEOUT 5  // Timeout for receiving acknowledgement (in seconds)

// Generates a random string of specified length
char* generate_random_string(int length) {
  char* string = malloc(length + 1);  // Allocate memory for the string
  for (int i = 0; i < length; i++) {
    // Generate a random character and append it to the string
    char c = 'A' + rand() % 26;
    string[i] = c;
  }
  string[length] = '\0';  // Add null terminator
  return string;
}

int main() {
  int shmid;
  char* shared_memory;  // Pointer to shared memory
  char* strings[N];  // Array to store the strings

  // Create shared memory
  shmid = shmget(SHM_KEY, N * LENGTH, IPC_CREAT | 0666);
  if (shmid < 0) {
    perror("Error creating shared memory");
    exit(EXIT_FAILURE);
  }

  // Attach shared memory
  shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == (char*) -1) {
    perror("Error attaching shared memory");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < N; i++) {
    strings[i] = generate_random_string(LENGTH);  // Generate and store a random string
  }

  int current_id = 0;  // ID of the first string in the current group
  while (current_id < N) {
    // Write a group of strings to shared memory
    for (int i = 0; i < GROUP_SIZE; i++) {
      int id = current_id + i;  // ID of the current string
      if (id >= N) {
        break;  // No more strings to send
      }
      char* string = strings[id];  // String to send
      memcpy(shared_memory + id * LENGTH, &id, sizeof(id));  // Write ID to shared memory
      memcpy(shared_memory + id * LENGTH + sizeof(id), string, LENGTH);  // Write string to shared memory
    }

    // Wait for acknowledgement from P2
    sleep(TIMEOUT);
  }

  // Detach and remove shared memory
  if (shmdt(shared_memory) < 0) {
    perror("Error detaching shared memory");
    exit(EXIT_FAILURE);
  }
  if (shmctl(shmid, IPC_RMID, NULL) < 0) {
    perror("Error removing shared memory");
    exit(EXIT_FAILURE);
  }

