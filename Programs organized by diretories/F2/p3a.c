// LIST THE CONTENTS OF A TEXT FILE TO THE TERMINAL
// USAGE: p3a <text file> 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define LENGTH 1024

int main(int argc, char *argv[]) {
  int src, nr;
  char *buffer[LENGTH];
  
  if (argc != 2) {
    printf("Usage: %s <text file>\n", argv[0]);
    return 1;
  }
  if ((src = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    return 2;
  }
  while ((nr=read(src, buffer, LENGTH)) != 0)
    write(STDOUT_FILENO, buffer, nr);           // write the same nr of read bytes on the terminal
  close(src);
  return 0;
}
