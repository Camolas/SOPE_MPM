#include <stdio.h>
#include <errno.h>

#define BUF_LENGTH 256

/* copia um ficheiro de texto para outro */

int main(int argc, char* argv[]) {
  FILE *src, *dst;
  char buf[BUF_LENGTH];
  
  if (argc != 3) {                                  // nr. errado de parâmetros e "Usage"
    printf("Usage: %s <source file name> <destination file name>\n", argv[0]);
    return 1;
  }
  if ( (src=fopen(argv[1], "r")) == NULL ) {        // abrir 1º file
    perror(argv[1]);                                // imprimir mensagem de erro relativa ao 1º ficheiro
    printf("errno = %d\n", errno);
    return 2;
  }
  if ( (dst=fopen(argv[2], "w")) == NULL ) {        // abrir 2º ficheiro (escrita)
    perror(argv[2]);                                // mprimir mensagem de erro relativa ao 2º ficheiro
    printf("errno = %d\n", errno);
    return 3;
  }
  while ( fgets(buf, BUF_LENGTH, src)!=NULL )       // copiar linha a linha o 1º para o 2º ficheiro
    fputs(buf, dst);
  fclose(src);
  fclose(dst);
  return 0;                                         // terminação sem erro
}
