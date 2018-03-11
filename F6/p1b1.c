#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 

#define STDERR 2 
#define NUMITER 10000

void * thrfunc(void * arg) { 
  int i;
  
  fprintf(stderr, "Starting thread %c\n", *(char *) arg); 
  for (i = 1; i <= NUMITER; i++)
    write(STDERR, arg, 1); 
  return NULL; 
}

int main() {
  char a; 
  pthread_t ta, tb;
  
  a = '1';
  pthread_create(&ta, NULL, thrfunc, &a);
  a = '2'; 
  pthread_create(&tb, NULL, thrfunc, &a); 
  pthread_join(ta, NULL); 
  pthread_join(tb, NULL); 
  return 0; 
}
