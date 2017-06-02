// LIST THE CONTENTS OF A TEXT FILE ON THE TERMINAL OR A FILE
// USAGE: p3b <text file> [<destination>]

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define LENGTH 1024

int main(int argc, char *argv[]) {
  int src, dst, nr;
  char *buffer[LENGTH];
  
  if (!(argc == 2 || argc == 3)) {
    printf("Usage: %s <text file> [<destination>]\n", argv[0]);
    return 1;
  }
  if ((src = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    return 2;
  }
  if (argc == 3) {
    if ((dst = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600)) == -1) {
      perror(argv[2]);
      return 3;
    }
    dup2(dst, STDOUT_FILENO);                   // redirect STDOUT_FILENO to dst
  }
  while ((nr=read(src, buffer, LENGTH)) != 0)
    write(STDOUT_FILENO, buffer, nr);           // write the same nr of bytes on the terminal or file
  close(src);
  return 0;
}
