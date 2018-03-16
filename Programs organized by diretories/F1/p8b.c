#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

/*   Medida de tempos de execução
     Gera números aleatórios entre 0 e o 1º parâmetro (exclusivé)
     Termina quando gerar um número aletório igual ao 2º parâmetro
*/

int main(int argc, char *argv[]) {         // acesso a parâmetros
  int m, n, r, k=1;
  long tcks;
  clock_t t1, t2;
  struct tms clocks;

  if (argc != 3) {                         // nr. errado de parâmetros
    printf("Usage: %s <max random> <nr to match>\n", argv[0]);
    return 1;
  }
  m = atoi(argv[1]);                       // conversões para valores int
  n = atoi(argv[2]);
  if (m<=0 || n<0 || n>=m) {               // valores inválidos
    printf("Invalid values!\n");
    return 2;
  }
  srand(time(NULL));                       // inicialização do gerador de números aleatórios
                                           // time(NULL) retorna a hora atual em segundos (desde 1/1/1970)
  tcks = sysconf(_SC_CLK_TCK);             // nr. de ticks por segundo deste sistema
  t1 = times(NULL);                        // começa a medida de tempo
  do {
    r = rand() % m;
    printf("%d %d\n", k, r);
    k++;
  } while (r != n);                        // gera e imprime até encontrar um igual ao 2º parâmetro
  t2 = times(&clocks);                     // termina a medida de tempo
  printf("Elaspsed time: %.3f s\n", (double)(t2-t1)/tcks);   // a diferença é o tempo gasto
  printf("Processor: User: %.3f s   System: %.3f s\n", (double)clocks.tms_utime/tcks, (double)clocks.tms_stime/tcks);
                                           // tempos de CPU em código do programa e de sistema
  return 0;                                // terminação sem erro
}
