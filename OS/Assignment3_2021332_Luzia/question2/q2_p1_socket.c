#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/socket"
#define NUM_STRINGS 50
#define STRING_LENGTH 10
#define GROUP_SIZE 5

int main() {
  int sockfd, len, result;
  struct sockaddr_un address;
  int str_idx = 0;
  char **strings = malloc(NUM_STRINGS * sizeof(char*));
  char buffer[GROUP_SIZE * (STRING_LENGTH + 1)];

  // Generate random strings
  for (int i = 0; i < NUM_STRINGS; i++) {
    strings[i] = malloc(STRING_LENGTH + 1);
    for (int j = 0; j < STRING_LENGTH; j++) {
      strings[i][j] = (char)('a' + rand() % 26);
    }
    strings[i][STRING_LENGTH] = '\0';
  }

  // Create socket
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Socket error");
    exit(1);
  }

  // Set up server address
  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, SOCKET_NAME);
  len = sizeof(address);

  // Connect to server
  result = connect(sockfd, (struct sockaddr*) &address, len);
  if (result == -1) {
    perror("Connect error");
    exit(1);
  }

  // Send strings in groups of size GROUP_SIZE
  while (str_idx < NUM_STRINGS) {
    // Build message to send
    buffer[0] = '\0';
    for (int i = 0; i < GROUP_SIZE && str_idx + i < NUM_STRINGS; i++) {
      char str_idx_str[11];
      sprintf(str_idx_str, "%d", str_idx + i);
      strcat(buffer, str_idx_str);
      strcat(buffer, ":");
      strcat(buffer, strings[str_idx + i]);
      strcat(buffer, ",");
    }

    // Send message
    result = write(sockfd, buffer, strlen(buffer));
    if (result == -1) {
      perror("Write error");
      exit(1);
    }

    // Wait for acknowledgement
    result = read(sockfd, buffer, GROUP_SIZE * (STRING_LENGTH + 1));
    if (result == -1) {
      perror("Read error");
      exit(1);
    }

    // Update string index
    str_idx = atoi(buffer) + 1;
  }

 
