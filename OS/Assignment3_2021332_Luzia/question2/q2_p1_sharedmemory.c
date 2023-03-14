#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
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
  int shm_id;
  char* shm_ptr;
  char* strings[N];  // Array to store the strings

  // Create shared memory
  shm_id = shmget(SHM_KEY, N * LENGTH, IPC_CREAT | 0666);
  if (shm_id < 0) {
    perror("Error creating shared memory");
    exit(EXIT_FAILURE);
  }

  // Attach shared memory to the process
  shm_ptr = shmat(shm_id, NULL, 0);
  if (shm_ptr == (char*) -1) {
    perror("Error attaching shared memory");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < N; i++) {
    strings[i] = generate_random_string(LENGTH);  // Generate and store a random string
  }

  int current_id = 0;  // ID of the first string in the current group
  while (current_id < N) {
    // Send a group of strings to P2
    for (int i = 0; i < GROUP_SIZE; i++) {
      int id = current_id + i;  // ID of the current string
      if (id >= N) {
        break;  // No more strings to send
      }
      char* string = strings[id];  // String to send
      memcpy(shm_ptr + id * LENGTH, &id, sizeof(id));  // Write ID to shared memory
      memcpy(shm_ptr + id * LENGTH + sizeof(id), string, LENGTH);  // Write string to shared memory
    }

    // Wait for acknowledgement from P2
    sleep(TIMEOUT);
  }

  // Detach shared memory and delete it
  shmdt(shm_ptr);
  shmctl(shm_id, IPC_RMID, NULL);

  return 0;
}