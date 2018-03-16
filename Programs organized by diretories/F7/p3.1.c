#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXELEMS 10000000              // nr. max de posicoes
#define MAXTHREADS 100                 // nr. max de threads
#define min(a, b) (a)<(b)?(a):(b)

int npos;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;    // mutex p/a sec.critica
pthread_mutex_t vmut=PTHREAD_MUTEX_INITIALIZER;
int buf[MAXELEMS], pos=0, val=0, ver=0;             // variaveis partilhadas

void *fill(void *nr) {
  while (1) {
    pthread_mutex_lock(&mut);
    if (pos >= npos) {
      pthread_mutex_unlock(&mut);
      return NULL;
    }
    buf[pos] = val;
    pos++; val++;
    pthread_mutex_unlock(&mut);
    *(int *)nr += 1;
  }
}

void *verify(void *arg) {
  while (1) {
    pthread_mutex_lock(&vmut);
    if (ver >= npos) {
      pthread_mutex_unlock(&vmut);
      return NULL;
    }
    if (ver < pos) {
      if (buf[ver] != ver)
        printf("ERROR: buf[%d] = %d\n", ver, buf[ver]);
      ver++;
      pthread_mutex_unlock(&vmut);
      *(int *)arg += 1;
    }
    else
      pthread_mutex_unlock(&vmut);
  }
}

int main(int argc, char *argv[]) {
  int k, nthr, nv, count[MAXTHREADS], v[MAXTHREADS];  // arrays para contagens
  pthread_t tidf[MAXTHREADS], tidv[MAXTHREADS];       // tids dos threads
  int total, tver;

  if (argc != 4) {
    printf("Usage: %s <nr_pos> <nr_thrs> <nr_tverify>\n",argv[0]);
    return 1;
  }
  npos = min(atoi(argv[1]), MAXELEMS);          //no. efectivo de posicoes
  nthr = min(atoi(argv[2]), MAXTHREADS);        //no. efectivo de threads
  nv = min(atoi(argv[3]), MAXTHREADS);          //no. efectivo de threads verify
  
  for (k=0; k<nthr; k++) {                      // criacao das threads 'fill'
    count[k] = 0;
    pthread_create(&tidf[k], NULL, fill, &count[k]);
  }
  for (k=0; k<nv; k++) {                       // criacao das threads 'verify'
    v[k] = 0;
    pthread_create(&tidv[k], NULL, verify, &v[k]);
  }
  
  total = 0;
  for (k=0; k<nthr; k++) {                      //espera threads 'fill'
    pthread_join(tidf[k], NULL);
    printf("count[%d] = %d\n", k, count[k]);
    total += count[k];
  }
  tver = 0;
  for (k=0; k<nv; k++) {                        //espera threads 'verify'
    pthread_join(tidv[k], NULL);
    printf("ver[%d] = %d\n", k, v[k]);
    tver += v[k];
  }
  pthread_mutex_destroy(&mut);
  pthread_mutex_destroy(&vmut);
  printf("total count = %d  total verified = %d\n",total, tver);
  return 0;
}
