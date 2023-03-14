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
  int sockfd, newsockfd, len, result;
  struct sockaddr_un address;
  int str_idx = 0;
  char buffer[GROUP_SIZE * (STRING_LENGTH + 1)];

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

  // Bind socket to server address
  result = bind(sockfd, (struct sockaddr*) &address, len);
  if (result == -1) {
    perror("Bind error");
    exit(1);
  }

  // Listen for incoming connections
  result = listen(sockfd, 5);
  if (result == -1) {
    perror("Listen error");
    exit(1);
  }

  // Accept incoming connection
  newsockfd = accept(sockfd, (struct sockaddr*) &address, &len);
  if (newsockfd == -1) {
    perror("Accept error");
    exit(1);
  }

  // Receive strings in groups of size GROUP_SIZE
  while (str_idx < NUM_STRINGS) {
    // Read message
    result = read(newsockfd, buffer, GROUP_SIZE * (STRING_LENGTH + 1));
    if (result == -1) {
      perror("Read error");
      exit(1);
    }

    // Extract strings and IDs from message
    int max_id = 0;
    char *token = strtok(buffer, ",");
    while (token != NULL) {
      // Split ID and string
      char *split = strchr(token, ':');
      if (split == NULL) {
        printf("Invalid message format\n");
        exit(1);
      }
      *split = '\0';
      int id = atoi(token);
      char *str = split + 1;

      // Print ID and string
      printf("ID: %d, String: %s\n", id, str);

      // Update maximum ID
      if (id > max_id) {
        max_id = id;
      }

      // Get next token
      token = strtok(NULL, ",");
    }

    // Send acknowledgement
    sprintf(buffer, "%d", max_id);
    result = write(newsockfd, buffer, strlen(buffer));
    if (result == -1) {
      perror("Write error");
      exit(1);
    }
  }
    
}