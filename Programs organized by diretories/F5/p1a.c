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
    int a, b; 

    printf("PARENT:\n"); 
    printf("x y ? "); scanf("%d %d", &a, &b); 
    close(fd[READ]); 
    write(fd[WRITE], &a, sizeof(int)); 
    write(fd[WRITE], &b, sizeof(int)); 
    close(fd[WRITE]); 
  } 
  else {             //filho 
    int x, y; 

    close(fd[WRITE]); 
    read(fd[READ], &x, sizeof(int));
    read(fd[READ], &y, sizeof(int));
    printf("SON:\n");
    printf("x + y = %d\n", x+y); 
    close(fd[READ]); 
  } 
  return 0; 
} 
