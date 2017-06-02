#include <stdio.h> 
#include <unistd.h> 
#include <sys/stat.h> 
#include <string.h>
#include <fcntl.h>

#define MAX_MSG_LEN 20 

int main() { 
  int fd, n, fd_dummy; 
  char str[MAX_MSG_LEN]; 

  if ((fd = open("/tmp/fifo_chg", O_RDONLY)) == -1) {
    perror("/tmp/fifo_chg");
    return 1;
  }
  else
    printf("FIFO openned in READONLY mode\n"); 
  if ((fd_dummy = open("/tmp/fifo_chg", O_WRONLY)) != -1) 
    printf("FIFO openned in WRITEONLY mode\n"); 
  do { 
    n = read(fd, str, MAX_MSG_LEN); 
    if (n>0)
      printf("CHEGOU %s\n", str); 
  } 
  while (strcmp(str,"SHUTDOWN") != 0); 
  close(fd); 
  close(fd_dummy); 
  return 0; 
} 
