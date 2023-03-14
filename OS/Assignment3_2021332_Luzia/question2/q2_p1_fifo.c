#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/my_fifo"
#define NUM_STRINGS 50
#define STRING_LENGTH 10
#define GROUP_SIZE 5

int main(int argc, char* argv[]) {
  // Create the FIFO if it doesn't exist
  mkfifo(FIFO_NAME, 0666);

  int fd = open(FIFO_NAME, O_WRONLY);
  if (fd < 0) {
    perror("Error opening FIFO");
    return 1;
  }

  // Generate an array of random strings
  char strings[NUM_STRINGS][STRING_LENGTH];
  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < STRING_LENGTH; j++) {
      strings[i][j] = rand() % 26 + 'a';
    }
  }

  int next_id = 0;
  while (next_id < NUM_STRINGS) {
    // Send a group of strings to P2
    for (int i = 0; i < GROUP_SIZE; i++) {
      int id = next_id + i;
      char* str = strings[id];
      write(fd, &id, sizeof(id));
      write(fd, str, sizeof(char) * STRING_LENGTH);
    }

    // Wait for P2 to acknowledge receipt of the strings
    int acknowledged_id;
    read(fd, &acknowledged_id, sizeof(acknowledged_id));

    // Update the starting index for the next group of strings
    next_id = acknowledged_id + 1;
  }

  close(fd);

  return 0;
}
