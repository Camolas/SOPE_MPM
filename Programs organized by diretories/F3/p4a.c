// PROCESSO PAI ESPERA QUE O FILHO TERMINE

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  
  pid = fork();
  if (pid == 0) {               // processo filho
    printf("Hello ");
    return 0;                   // termina
  }
  if (pid > 0) {
    wait(NULL);                 // processo pai espera que filho termine
    printf("world!\n");
    return 0;
  }
}
