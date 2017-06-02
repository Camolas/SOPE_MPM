#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
  int a, b;
} args;

void *thr_multiply(void *arg) {
  int *ret;
  args *vls;

  ret = (int *) malloc(sizeof(int));
  vls = (args *) arg;
  *ret = vls->a * vls->b;
  return (void *)ret;
}

void *thr_divide(void *arg) {
  double *ret;
  args *vls;

  ret = (double *) malloc(sizeof(double));
  vls = (args *) arg; //  cast de estrututura pointer...
  *ret = (double)(vls->a) / vls->b;
  return (void *)ret;
}


int main(int argc, char *argv[]) {
  args vals;
  pthread_t t1, t2;
  int* res1;// modo Leixo
  double* res2;

  if (argc != 3) {
    printf("Usage: %s <val1> <val2>\n", argv[0]);
    return 1;
  }
  vals.a = atoi(argv[1]);
  vals.b = atoi(argv[2]);
  if (vals.b == 0) {
    printf("Second value cannot be 0\n");
    return 1;
  }
  pthread_create(&t1, NULL, thr_multiply, &vals);
  pthread_create(&t2, NULL, thr_divide, &vals);

  pthread_join(t1, (void **)&res1);
  printf("%d x %d = %d\n", vals.a, vals.b, *res1);
  free(res1);
  pthread_join(t2, (void **)&res2);
  printf("%d / %d = %f\n", vals.a, vals.b, *res2);
  free(res2);
  return 0;
}
