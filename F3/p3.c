// 2 PROCESSOS EM EXECUÇÃO

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX 50000

int main() {
  int i;
  pid_t pid;
  char str[10];
  
  pid = fork();
  switch (pid) {
    case -1:                            // erro na criação do processo
      perror("fork");
      break;
    case 0:                             // processo filho
      for (i=1; i<=MAX; i++) {
        sprintf(str, "-%d", i);
        write(STDOUT_FILENO, str, strlen(str));
      }
      break;
    default:                            // processo pai
      for (i=1; i<=MAX; i++) {
        sprintf(str, "+%d", i);
        write(STDOUT_FILENO, str, strlen(str));
      }
  }
  return 0;
}
