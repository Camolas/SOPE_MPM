// PRESENT SOME DATA ABOUT THE ENTRIES IN A DIRECTORY
// USAGE: p6b <directory>

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  DIR *dirp;
  struct dirent *direntp;
  struct stat stat_buf;
  char *str;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <dir name>\n", argv[0]);
    exit(1);                                                // terminates the program with code 1
  }

  if ((dirp = opendir(argv[1])) == NULL) {
    perror(argv[1]);
    exit(2);
  }

  chdir(argv[1]);                                          // make the dir the current directory
  while ((direntp = readdir(dirp)) != NULL) {              // read each entry in the directory
    if (lstat(direntp->d_name, &stat_buf)==-1) {           // get entry data with lstat
      perror("lstat");
      exit(3);
    }
    if (S_ISREG(stat_buf.st_mode))
      str = "regular";
    else if (S_ISDIR(stat_buf.st_mode))
      str = "directory";
    else
      str = "other";
    printf("%-25s - %10lu %10lu %s\n", direntp->d_name, stat_buf.st_ino, stat_buf.st_size, str);
  }

  closedir(dirp);
  exit(0);
}

