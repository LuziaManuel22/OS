
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/my_fifo"
#define NUM_STRINGS 50
#define STRING_LENGTH 10

int main(int argc, char* argv[]) {
  // Open the FIFO for reading
  int fd = open(FIFO_NAME, O_RDONLY);
  if (fd < 0) {
    perror("Error opening FIFO");
    return 1;
  }

  int highest_id = -1;
  while (1) {
    // Read the ID and string from the FIFO
    int id;
    char str[STRING_LENGTH];
    read(fd, &id, sizeof(id));
    read(fd, str, sizeof(char) * STRING_LENGTH);

    // Print the ID and string
    printf("Received string with ID %d: %s\n", id);
  }