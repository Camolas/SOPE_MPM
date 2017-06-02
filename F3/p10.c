// USO DE EXECLP COM REDIRECIONAMENTO

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int fd;

  if (argc != 2 && argc != 3) {
    printf("Usage: %s <dir name> [<file>]\n", argv[0]);
    return 1;
  }
  pid = fork();
  if (pid > 0) {                                  // father
    printf("My child is going to execute \"ls -laR %s\"", argv[1]);
    if (argc == 3)
      printf(" > %s", argv[2]);
    printf("\n");
  }
  else if (pid == 0) {                            // son
    if (argc == 3) {                              // result should be in a file
      if ((fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1) {
        perror(argv[2]);
        return 1;
      }
      dup2(fd, STDOUT_FILENO);                    // redirect STDOUT to the file
    }
    execlp("ls", "ls", "-laR", argv[1], NULL);
    perror("execl");
    return 1;
  }
  wait(NULL);
  return 0;
} 
