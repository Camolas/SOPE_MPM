#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "p4.h"

int main(int argc, char *argv[]) {
  int fdmem, k, sz;
  struct shmdata *mem;
  
  if (argc!=3) {
    printf("Don't use %s directly!\n", argv[0]);
    return 1;
  }
  sz = sizeof(struct shmdata);
  fdmem = shm_open(argv[2], O_RDWR, 0600);
  if (fdmem == -1) {
    perror(argv[2]);
    return 1;
  }
  mem = mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, 0);
  k = 0;
  while (1) {
    if (mem->buf[k] != k)
      printf("buf[%d] = %d\n", k, mem->buf[k]);
    k++;
    if (k >= mem->npos) {
      printf("Verified: %d positions\n", k);
      break;
    }
  }
  munmap(mem, sz);
  close(fdmem);
  return 0;
}  
