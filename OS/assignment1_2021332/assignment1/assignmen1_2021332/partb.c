#include "header.h"
#include <pthread.h>

struct arguments {
   char args[FILE_PATH_LENGTH];
} arguments;

void *execute_program_thread(void *args){

   struct arguments *params = (struct arguments*)malloc(sizeof(struct arguments));

   params = (struct arguments*)args;

   char _arguments[FILE_PATH_LENGTH];

   memccpy(_arguments, params->args, sizeof(params->args), sizeof(_arguments));

   if (system(_arguments) < 0){
      perror("system");
   }

   return NULL;
   pthread_exit(&params);
}

void handle_internal_commands(char *command, int argc, void* args)  { //funcao para internos 
   if (strcmp(command, "cd") == 0){
      call_cd(argc, args);
   } else if (strcmp(command, "echo") == 0) {
     call_echo(argc, args);
   } else if (strcmp(command, "pwd") == 0) {
     call_pwd();
   }
}

void handle_external_commands(char command[FILE_PATH_LENGTH]) { 
   pthread_t th;
   
   pthread_create(&th, NULL, execute_program_thread, (void *)command);
   int* ptr;
   pthread_join(th, (void**)&ptr);
}

int is_in(char *command,int size, char commands[][9]){ 
   int found = 0;
   
   for (int i = 0; i < size; i++){
      int result = strcmp(command, commands[i]);
      if (result == 0) {
         found = 1;
      }
   }

   return found;
}

int main(int argc , char *argv) { 
   char internals[][9] = {"cd", "echo", "pwd"};
   char externals[][9] = {"ls","cat","date","rm","mkdir"};
   char user_input[FILE_PATH_LENGTH];
   char *commands[MAX_COMMANDS]; //user command[cd, ls, mkdir and etc..]

   for(;;){
      if (getcwd(current_directory, DIR_LENGTH) < 0){
         perror("current directory");
         exit(EXIT_FAILURE);
      } //get current directory

      printf("❤️  %s -> ", current_directory);
      if (!fgets(user_input, FILE_PATH_LENGTH, stdin) < 0){
         perror("user input");
      }
     
      char *token;
      int argument_count = 0;
      token = strtok(user_input, " ");

      while (token != NULL){
         commands[argument_count]  = token;
         token = strtok(NULL, " ");
         argument_count++; //update argument count
      }
  
      if (is_in(commands[0], INTERNAL_SIZE, internals) == 1){ 
         handle_internal_commands(commands[0], argument_count, (void*)commands);
      } else if (is_in(commands[0], EXTERNAL_SIZE, externals) == 1) { 
         char *command_input = malloc(FILE_PATH_LENGTH * sizeof(char*));
         for (int i = 0; i < argument_count - 1; i++){
            strcat(command_input, commands[i]);
            strcat(command_input, " ");
         }
         
        handle_external_commands(command_input);
      } else if (strcmp(commands[0], "q") == 0){
        printf("<quitting the shell..>\n");
        exit(EXIT_SUCCESS); 
      }  else {
        printf("Command not found\n"); 
      }
   }
  
   return 0;
}
