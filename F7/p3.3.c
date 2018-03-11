#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPOS 10000000                           /* nr. max de posições */
#define MAXTHRS 100                                /* nr. max de threads */
#define min(a, b) (a)<(b)?(a):(b)

int npos;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;      /* mutex para a s.c. */
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int buf[MAXPOS], pos=0, val=0, v=0;                 /* variáveis partilhadas */

void *fill(void *);
void *verify(void *);

int main(int argc, char *argv[])
{
  int k, nthr, total, count[MAXTHRS];               /* array para contagens */
  pthread_t tidf[MAXTHRS], tidv;                    /* tid's dos threads */

  if (argc != 3) {
    printf("Usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
    return 1;
  }
  npos = min(atoi(argv[1]), MAXPOS);         /* nr. efectivo de posições */
  nthr = min(atoi(argv[2]), MAXTHRS);         /* nr. efectivo de threads */
  pthread_create(&tidv, NULL, verify, NULL);
  for (k=0; k<nthr; k++) {
    count[k] = 0;                          /* criação dos threads fill() */
    pthread_create(&tidf[k], NULL, fill, &count[k]);
  }
  total = 0;
  for (k=0; k<nthr; k++) {
    pthread_join(tidf[k], NULL);          /* espera pelos threads fill() */
    printf("count[%d] = %d\n", k, count[k]);
    total += count[k];
  }
  printf("Total filled = %d\n", total);
  pthread_join(tidv, NULL);                        /* thread verificador */
  printf("Verified = %d\n", v);
  pthread_mutex_destroy(&mut);
  pthread_cond_destroy(&cond);
  return 0;
}

void *fill(void *nr)
{
  while (1) {
    pthread_mutex_lock(&mut);
    if (pos >= npos) {                            /* terminou o serviço */
      pthread_mutex_unlock(&mut);
      return NULL;
    }
    buf[pos] = val;
    pos++; val++;
    if (v < pos)
      pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mut);
    *(int *)nr += 1;
  }
}

void *verify(void *arg)
{
  while (1) {
    pthread_mutex_lock(&mut);
    if (v >= npos) {                              /* terminou o serviço */
      pthread_mutex_unlock(&mut);
      return NULL;
    }
    while (v >= pos)
      pthread_cond_wait(&cond, &mut);
    if (buf[v] != v)	                           /* escreve se encontrar valores errados */
      printf("buf[%d] = %d\n", v, buf[v]);
    v++;
    pthread_mutex_unlock(&mut);
  }
}
