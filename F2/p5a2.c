// WRITE 10 CHARACTERS TO A FILE ALREADY EXISTING
// EACH WRITE RETURNS AFTER THE BYTES ARE ALREADY RECORDED ON THE FILE

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
  int fd;
  char *filename = "f1.txt";
  char *text1 = "CCCCC";
  char *text2 = "DDDDD";

  if ((fd = open(filename, O_WRONLY|O_SYNC, 0600)) == -1) {  // permissions: rw-------
    perror(filename);
    return 1;
  }
  write(fd, text1, 5);
  write(fd, text2, 5);
  close(fd);
  return 0;
}

