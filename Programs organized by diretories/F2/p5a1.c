// WRITE 12 CHARACTERS TO FILE CREATED WITHOUT EXISTING
// EACH WRITE RETURNS AFTER THE BYTES ARE ALREADY RECORDED ON THE FILE

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
  int fd;
  char *filename = "f1.txt";
  char *text1 = "AAAAAA";
  char *text2 = "BBBBBB";

  if ((fd = open(filename, O_WRONLY|O_CREAT|O_EXCL|O_SYNC, 0600)) == -1) {
    perror(filename);
    return 1;
  }
  write(fd, text1, 6);
  write(fd, text2, 6);
  close(fd);
  return 0;
}

