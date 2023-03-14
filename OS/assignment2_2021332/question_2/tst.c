#define R 2
#define C 3

#include <unistd.h>
#include <stdio.h>

int main(){
  double a[R][C] = {{2.3, 5.6, 50.2}, {10.32, 20.5, 15.9}};
  double b[R][C];
  int size = R * C;

  printf("Calling the system call ...\n");
  
  syscall(548, size, *a, *b);


 for (int i = 0; i <  R; i++) {
      for (int j = 0; j < C; j++) {
        printf("%2.f ", (float)b[i][j]);
      }
      printf("\n");
  } 
  return 0;
}
