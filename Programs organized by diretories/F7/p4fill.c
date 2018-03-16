#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#include "p4.h"

int main(int argc, char *argv[]) {
  int fdmem, sz, nr;
  sem_t *sem;
  struct shmdata *mem;
  
  if (argc!=3) {
    printf("Don't use %s directly!\n", argv[0]);
    return 1;
  }
  sz = sizeof(struct shmdata);
  sem = sem_open(argv[1], O_RDWR);
  if (sem == SEM_FAILED) {
    perror(argv[1]);
    return 1;
  }
  fdmem = shm_open(argv[2], O_RDWR, 0600);
  if (fdmem == -1) {
    perror(argv[2]);
    return 1;
  }
  mem = mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, 0);
  nr = 0;
  while(1) {
    sem_wait(sem);
    if (mem->pos >= mem->npos) {
      sem_post(sem);
      break;
    }
    mem->buf[mem->pos] = mem->val;
    mem->pos++;
    mem->val++;
    sem_post(sem);
    nr++;
  }
  printf("Filled %d positions\n", nr);
  sem_wait(sem);
  mem->total += nr;
  sem_post(sem);
  sem_close(sem);
  munmap(mem, sz);
  close(fdmem);
  return 0;
}  
