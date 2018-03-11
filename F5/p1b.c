#include <stdio.h> 
#include <unistd.h> 

#define READ 0 
#define WRITE 1 

int main() { 
  int fd[2]; 
  pid_t pid; 
  
  pipe(fd); 
  pid = fork(); 
  if (pid >0) {      //pai
    struct { 
      int a, b;
    } sn;N

    printf("PARENT:\n"); 
    printf("x y ? "); scanf("%d %d", &(sn.a), &(sn.b)); 
    close(fd[READ]); 
    write(fd[WRITE], &sn, sizeof(sn)); 
    close(fd[WRITE]); 
  } 
  else {             //filho
    struct {
      int x, y;
    } vals;

    close(fd[WRITE]); 
    read(fd[READ], &vals, sizeof(vals));
    printf("SON:\n");
    printf("x + y = %d\n", vals.x+vals.y); 
    close(fd[READ]); 
  } 
  return 0; 
} 
