#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int increment = 1;

void handler(int signo) {
  if (signo == SIGUSR1)
    increment = 1;
  if (signo == SIGUSR2)
    increment = -1;
}

int main() {
  int value = 100;

  if (signal(SIGUSR1, handler) == SIG_ERR) {
    perror("SIGUSR1");
    return 1;
  }
  if (signal(SIGUSR2, handler) == SIG_ERR) {
    perror("SIGUSR2");
    return 1;
  }
  while(1) {
    printf("Value = %d\n", value);
    value += increment;
    sleep(1);
  }
  return 0;
}
