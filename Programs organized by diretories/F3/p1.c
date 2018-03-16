// VARS GLOBAIS E LOCAIS NA CRIAÇÃO DE PROCESSOS

#include <unistd.h>
#include <stdio.h>

int global = 1;

int main() {
  int local = 2;
  if (fork() > 0) {                                          // processo pai (recebe PID do filho)
    printf("PID = %d; PPID = %d\n", getpid(), getppid());
    global++;
    local--;
  }
  else {                                                     // processo filho
    printf("PID = %d; PPID = %d\n", getpid(), getppid());
    global--;
    local++;    
  }
  printf("PID = %d; global = %d; local = %d\n", getpid(), global, local);  // ambos executam esta linha
  return 0;
}
