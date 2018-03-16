// ESCRITA NO TERMINAL DIRETA POR 2 PROCESSOS

#include <unistd.h>

int main() {
  write(STDOUT_FILENO, "1", 1);        // antes de fork() (só uma vez)
  if (fork() > 0) {                    // pai
    write(STDOUT_FILENO, "2", 1);
    write(STDOUT_FILENO, "3", 1);
  }
  else {                               // filho
    write(STDOUT_FILENO, "4", 1);
    write(STDOUT_FILENO, "5", 1);
  }
  write(STDOUT_FILENO, "\n", 1);       // ambos
  return 0;
}
