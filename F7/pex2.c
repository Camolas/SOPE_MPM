#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int *i1, *i2, *i3, sz, smfd;
  char *flag;
  
  sz = 3*sizeof(int) + sizeof(char);
  smfd = shm_open("/shm1", O_RDWR, 0600);
  if (smfd == -1) {
    printf("nonexistent /shm1\n");
    return 1;
  }
  i1 = (int *)mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, smfd, 0);
  i2 = i1 + 1;
  i3 = i2 + 1;
  flag = (char *)(i3 +1);
  while (*flag != 1) {
  }
  *i3 = *i1 * *i2;
  *flag = 2;
  close(smfd);
  munmap(i1, sz);
  return 0;
}
