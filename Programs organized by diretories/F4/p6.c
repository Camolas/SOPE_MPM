#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid;
int forced;

void handler(int signo) {
  kill(pid, SIGKILL);
  forced = 1;
}

int main(int argc, char *argv[]) {
  int maxtime;

  if (argc < 3) {
    printf("%s <limit> <prog> [<args> ...]\n", argv[0]);
    return 1;
  }
  forced = 0;
  signal(SIGALRM, handler);
  maxtime = atoi(argv[1]);
  pid = fork();
  if (pid == 0) {
    execvp(argv[2], &argv[2]);
    perror(argv[2]);
    return 0;
  }
  alarm(maxtime);
  wait(NULL);
  if (forced)
    printf("%s with forced termination!\n", argv[2]);
  else
    printf("%s with natural termination\n", argv[2]);
  return 0;
}
