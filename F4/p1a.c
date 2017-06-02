#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
  printf("In SIGINT handler ...\n");
}

int main() {
  if (signal(SIGINT, sigint_handler) < 0) {
    perror("SIGINT");
    return 1;
  }
  printf("Sleeping for 30 seconds ...\n");
  sleep(30);
  printf("Waking up ...\n");
  return 0;
}
