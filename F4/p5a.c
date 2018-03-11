#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  int i, n;

  for (i=1; i<=3; i++) {
    //signal(SIGCHLD, SIG_IGN);
    pid = fork();
    if (pid == 0) {                                                 // processo filho
      printf("CHILD nr. %d (PID=%d) working ...\n", i, getpid());
      sleep(i*3);
      printf("CHILD nr. %d (PID=%d) leaving ...\n", i, getpid());
      return 0;                                                     // filho termina
    }
    printf("PARENT working hard ...\n");
    n = 12;
    while ((n = sleep(n)) >0);
  }
  printf("PARENT leaving ...\n");
  return 0;
}
