#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]) {     // acesso a variáveis de ambiente
  int k=0;
  char name[100];
  
  if (argc != 1) {                                   // invocar sem parâmetros
    printf("Usage: %s\n", argv[0]);
    return 1;
  }
  while (strncmp("USER=", envp[k], 5)!=0)            // descobrir a linha que começa por "USER="
    k++;
  strcpy(name, &envp[k][5]);                         // extrair o resto da linha
  printf("Hello %s!\n", name);
  return 0;
}
