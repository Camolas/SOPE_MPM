//PROBLEM SET 2 - p1.c
//READING A PASSWORD, WITHOUT ECHOING

#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PASSWD_LEN 20

int main() {
 struct termios term, oldterm;
 int i;
 char pass[MAX_PASSWD_LEN+1], ch, echo = '*';

 write(STDOUT_FILENO, "\nPassword? ", 11);

 tcgetattr(STDIN_FILENO, &oldterm);
 term = oldterm;
 term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
 tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);               // change terminal properties to not echoing

 i=0;
 while (i < MAX_PASSWD_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
  pass[i++] = ch;
  write(STDOUT_FILENO, &echo, 1);                         // echoing an '*'
 }
 pass[i] = 0;                                             // terminating the string (C style)

 tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);              // restore terminal properties
 write(STDOUT_FILENO, "\n\nPassword: ", 12);
 write(STDOUT_FILENO, pass, strlen(pass));
 write(STDOUT_FILENO, "\n", 1);

 return 0;
}

