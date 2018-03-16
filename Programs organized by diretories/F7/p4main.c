#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "p4.h"

#define MAXPROC 100
#define SEM "/semfill"
#define MEM "/membuf"
#define min(a,b) (a)<(b)?(a):(b)

int main(int argc, char* argv[]) {
  sem_t *sem;
  int fdmem, nproc, k, sz;
  struct shmdata *mem;
  pid_t pidf[MAXPROC], pidv;

  if (argc!=3) {
    printf("usage: %s <nr_pos> <nr_procs>\n", argv[0]);
    return 1;
  }
  sz = sizeof(struct shmdata);
  fdmem = shm_open(MEM, O_RDWR|O_CREAT, 0600);
  ftruncate(fdmem, sz);
  mem = mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, 0);
  sem = sem_open(SEM, O_RDWR|O_CREAT, 0600, 1);
  mem->npos = min(atoi(argv[1]), MAXPOS);
  mem->pos = mem->val = mem->total = 0;
  nproc = min(atoi(argv[2]), MAXPROC);
  for (k=0; k<nproc; k++) {
    pidf[k] = fork();
    if (pidf[k] == 0) {
      execl("./p4fill", "./p4fill", SEM, MEM, NULL);
      return 0;
    }
  }
  for (k=0; k<nproc; k++) {
    waitpid(pidf[k], NULL, 0);
  }
  printf("Total filled = %d positions\n", mem->total);
  pidv = fork();
  if (pidv == 0) {
    execl("./p4verify", "./p4verify", SEM, MEM, NULL);
    return 0;
  }
  waitpid(pidv, NULL, 0);
  
  sem_close(sem);
  sem_unlink(SEM);
  munmap(mem, sz);
  close(fdmem);
  shm_unlink(MEM);
  return 0;
}
