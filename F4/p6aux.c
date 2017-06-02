#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int k;
  
  for (k=1; k<=6; k++) {
    printf("%s\n", argv[1]);
    sleep(5);
  }
  printf("%s terminating\n", argv[0]);
  return 0;
}
