#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <fcntl.h> 

int main(int argc, char *argv[]) { 
  int fd;
  
  if (argc!=2) { 
    printf("Usage: %s <username>\n", argv[0]); 
    return 1; 
  } 
  fd = open("/tmp/fifo_chg", O_WRONLY); 
  if (fd == -1) { 
    perror("/tmp/fifo_chg"); 
    return 1; 
  } 
  printf("FIFO openned in WRITEONLY mode\n"); 
  write(fd, argv[1], strlen(argv[1])+1); 
  close(fd); 
  return 0; 
} 
