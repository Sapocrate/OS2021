#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf

int main(int argc, char const *argv[]) {
  int x=0;
  if (fork()==0) {
    x++;
    if (fork()==0) {
      x++;
    }
    else
      wait(NULL);
  }
  else
    wait(NULL);
  printf("%d\n", x);
  return 0;
}
