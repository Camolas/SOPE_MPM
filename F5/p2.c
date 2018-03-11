#include <stdio.h> 
#include <unistd.h> 

#define READ 0 
#define WRITE 1 

int main() { 
  int fd1[2], fd2[2]; 
  pid_t pid; 
  
  pipe(fd1);
  pipe(fd2); 
  pid = fork(); 
  if (pid > 0) {      //pai 
    int a, b, r; 

    close(fd1[READ]);
    close(fd2[WRITE]); 

    printf("x y ? "); scanf("%d %d", &a, &b); 

    write(fd1[WRITE], &a, sizeof(int)); 
    write(fd1[WRITE], &b, sizeof(int)); 
    close(fd1[WRITE]);
    
    read(fd2[READ], &r, sizeof(int));
    close(fd2[READ]);
    
    printf("x + y = %d\n", r);
  } 
  else {             //filho 
    int x, y, sum; 

    close(fd1[WRITE]);
    close(fd2[READ]);
    
    read(fd1[READ], &x, sizeof(int));
    read(fd1[READ], &y, sizeof(int));
    close(fd1[READ]);
    
    sum = x + y;
    
    write(fd2[WRITE], &sum, sizeof(int));
    close(fd2[WRITE]);
  } 
  return 0; 
} 
