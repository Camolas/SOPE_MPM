#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
  printf("In SIGINT handler ...\n");
}

int main() {
  unsigned int mysleep = 30;
  if (signal(SIGINT, sigint_handler) < 0) {
    perror("SIGINT");
    return 1;
  }
  printf("Sleeping for 30 seconds ...\n");
  while (mysleep > 0)
    mysleep = sleep(mysleep);
  printf("Waking up ...\n");
  return 0;
}
