#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#define INTERNAL_SIZE 3
#define EXTERNAL_SIZE 5 
#define PATH "/usr/bin"
#define DIR_LENGTH 1024
#define FILE_PATH_LENGTH 64
#define MAX_COMMANDS 10
#define MAX_ARG 5

char current_directory[DIR_LENGTH];
//internals functions
void call_cd(int argc, char *args[MAX_COMMANDS]){
 
    char *dir = args[1];
    char current_dir[DIR_LENGTH];

    strcpy(current_dir, current_directory);
    if (argc - 1 < 2){
        printf("few arguments passed to cd: it requires 1\n");
    } else {
        if (strcmp(dir, ".") != 0 || strcmp(dir, "..") != 0){
            char path[DIR_LENGTH];
            snprintf(path, strlen(current_dir) + DIR_LENGTH, "%s/%s", current_dir, dir);
            if (chdir(path) < 0){
                perror("chdir");
            }
        }
    }
}

void call_echo(int argc, char *args[MAX_COMMANDS]){
    if (argc - 1 < 2) {
        printf("few arguments passed to cd: it requires 1\n");
    } else {
        for (int i = 1; i < argc; i++){
            printf("%s ", args[i]);
        }
    }
}

void call_pwd(){
    printf("%s\n", current_directory);
}
