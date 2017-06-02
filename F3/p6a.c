// PROCESSOS FILHO QUE SE TORNAM ZOMBIES

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  int i, j;
  
  printf("I'm process %d. My parent is %d.\n", getpid(), getppid());
  for (i=1; i<=3; i++) {
    pid = fork();
    if (pid < 0) {
      perror("fork");
      return 1;
    }
    else if (pid == 0) {
      printf("I'm process %d. My parent is %d. I'm going to work for 1s ...\n", getpid(), getppid());
      sleep(1);
      printf("I'm process %d. My parent is %d. I finished my work.\n", getpid(), getppid());
      return 0;
    }
    else
      for (j=1; j<=10; j++) {
        sleep(1);
        printf("Father working ...\n");
      }
  }
  return 0;
}  
