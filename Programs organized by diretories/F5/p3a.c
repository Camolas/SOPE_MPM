#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

#define READ 0 
#define WRITE 1 

int main(int argc, char *argv[]) { 
  int fd[2]; 
  pid_t pid; 
  
  if (argc != 2) {
    printf("Usage: %s <text_file>\n", argv[0]);
    return 1;
  }
  pipe(fd);
  pid = fork(); 
  if (pid > 0) {      //pai 
    FILE *fp;

    close(fd[READ]);
    fp = fopen(argv[1], "r");
    if (fp != NULL) {
      char buffer[101];
      
      while (fgets(buffer, 101, fp) != NULL)
        write(fd[WRITE], buffer, strlen(buffer));
      fclose(fp);
    }
    close(fd[WRITE]);
    wait(NULL);
  } 
  else {             //filho 
    close(fd[WRITE]);
    dup2(fd[READ], STDIN_FILENO);
    execlp("sort", "sort", NULL);
    perror("sort");
  } 
  return 0; 
} 
