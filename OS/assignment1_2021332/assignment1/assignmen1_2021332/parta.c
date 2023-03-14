#include "header.h"

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

void handle_internal_commands(char *command, int argc, void* args)  
{
  
   if (strcmp(command, "cd") == 0){
      call_cd(argc, args);
   } else if (strcmp(command, "echo") == 0) {
     call_echo(argc, args);
   } else if (strcmp(command, "pwd") == 0) {
     call_pwd();
   }
}

void handle_external_commands(char *command, int argc, char *args[MAX_COMMANDS]) 
{
   pid_t pid;
   int status = 0;
   if ((pid = fork()) == 0){
      char file_path[FILE_PATH_LENGTH];
      char *env[] = { NULL };
      snprintf(file_path, FILE_PATH_LENGTH, "%s/%s", PATH, args[0]);
      char *arguments[MAX_ARG];

      args[argc] = NULL;
     
      if (execvp(file_path, args) < 0){
         perror("execvp");
      }
   } 
      
   wait(&status);
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
         handle_external_commands(commands[0], argument_count-1, (void*)commands);
      } else if (strcmp(commands[0], "q") == 0){
         printf("<quitting the shell..>\n");
         exit(EXIT_SUCCESS); 
      }  else {
         printf("Command not found\n"); 
      }
   }
  
   return 0;
}
