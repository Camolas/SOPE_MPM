#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
  printf("Entering SIGINT handler ...\n");
  sleep(10);
  printf("Leaving SIGINT handler ...\n");
}

int main() {
  struct sigaction action;

  action.sa_handler = sigint_handler;
  sigemptyset(&action.sa_mask);
  // sigaddset(&action.sa_mask, SIGTERM);       // test by masking out the SIGTERM signal
  action.sa_flags = 0;
  if (sigaction(SIGINT, &action, NULL) < 0) {
    perror("SIGINT");
    return 1;
  }
  printf("Try me with CTRL-C ...\n");
  while(1)
    pause();
  return 0;
}
