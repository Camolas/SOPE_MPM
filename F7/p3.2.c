#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAXPOS 10000000
#define MAXTHRS 100
#define min(a,b) (a)<(b)?(a):(b)

int npos;
int buf[MAXPOS], pos=0, val=0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

void *fill(void*);
void *verify(void*);

int main(int argc, char* argv[])
{
  int k, nthr, count[MAXTHRS], total;
  pthread_t tidf[MAXTHRS], tidv;

  if (argc!=3) {
    printf("usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
    return 1;
  }
  npos = min(atoi(argv[1]), MAXPOS);
  nthr = min(atoi(argv[2]), MAXTHRS);
  if (sem_init(&sem, 0, 0)== -1) {
    perror("sem");
    return 1;	
  }
  pthread_create(&tidv, NULL, verify, NULL);
  for (k=0;k<nthr;k++) {
    count[k] = 0;
    pthread_create(&tidf[k], NULL, fill, &count[k]);
  }
  total = 0;
  for (k=0; k<nthr; k++) {
    pthread_join(tidf[k], NULL);
    printf("count[%d] = %d\n", k, count[k]);
    total += count[k];
  }
  printf("Total filled = %d\n", total);
  pthread_join(tidv, NULL);
  pthread_mutex_destroy(&mut);
  sem_destroy(&sem);
  return 0;
}

void *fill(void *nr)
{
  while(1) {
    pthread_mutex_lock(&mut);
    if (pos >= npos) {
      pthread_mutex_unlock(&mut);
      return NULL;
    }
    buf[pos] = val;
    pos++;
    val++;
    sem_post(&sem);
    pthread_mutex_unlock(&mut);
    *(int *)nr += 1;
  }
}

void *verify(void *arg)
{
  int k=0;

  while (1) {
    sem_wait(&sem);
    if (buf[k] != k)
      printf("buf[%d] = %d\n", k, buf[k]);
    k++;
    if (k>=npos) {
      printf("Verified: %d\n", k);
      return NULL;
    }
  }
}
