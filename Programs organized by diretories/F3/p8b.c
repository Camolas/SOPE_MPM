// USO DE EXECL

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid;

  if (argc != 2) {
    printf("Usage: %s <dir name>\n", argv[0]);
    return 1;
  }
  pid = fork();
  if (pid > 0)                   // pai
    printf("My child is going to execute \"ls -laR %s\"\n", argv[1]);
  else if (pid == 0) {           // filho
    execl("/bin/ls", "ls", "-laR", argv[1], NULL);
    perror("execl");
    return 1;
  }
  wait(NULL);
  return 0;
} 
