#include <sys/mman.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int *i1, *i2, *i3, sz, smfd;
  char *flag;
  
  sz = 3*sizeof(int) + sizeof(char);
  smfd = shm_open("/shm1", O_RDWR|O_CREAT, 0600);
  ftruncate(smfd, sz);
  i1 = (int *)mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, smfd, 0);
  i2 = i1 + 1;
  i3 = i2 + 1;
  flag = (char *)(i3 + 1);
  *i1 = 21;
  *i2 = 41;
  *flag = 1;
  while (*flag != 2) {
  }
  printf("Result: %d\n", *i3);
  close(smfd);
  munmap(i1, sz);
  shm_unlink("/shm1");
  return 0;
}
