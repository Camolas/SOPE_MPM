// PROCESSO FILHO ESPERA QUE O PAI TERMINE

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
  pid_t pid, father;
  
  father = getpid();              // o pid do processo pai
  pid = fork();
  if (pid > 0) {                  // processo pai
    printf("Hello ");
  }
  if (pid == 0) {                 // filho 
    while (getppid() == father);  // quando o pai termina o filho é adotado por outro
    printf("world!\n");
    return 0;
  }
  return 0;                       // o pai termina
}
