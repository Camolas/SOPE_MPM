#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {            // parâmetros na linha de chamada do terminal
  int k, nr;
  
  if (argc != 3) {                            // se nr. errado de parâmetros 
    printf("Usage: %s <name> <nr of times>\n", argv[0]);
    return 1;
  }
  nr = atoi(argv[2]);                         // converter <nr of times> para int
  if (nr <= 0) {                              // valor de <nr of times> inválido
    printf("The nr of times should be greater than 0!\n");
    return 2;
  }
  for (k=0; k<nr; k++)                        // repetir saudação <nr> vezes
    printf("Hello %s!\n", argv[1]);
  return 0;
}
