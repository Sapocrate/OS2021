#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali

/*
Con n=4 mi aspetto che come output si abbia 4 3 2 1 End.
INVECE
un end per ogni processo (5 processi/ anche 0 viene chiamato ma non stampa)
perche la syscall system non e come la execute...
Il flow graph lineare, ogni processo con la systemcall system()
chiama lo stesso con n=n-1.
Cosa succede al PID?
*/

int main(int argc, char const *argv[]) {
  int n;
  char str[10];

  n=atoi(argv[1]);
  if(n>0){
    printf("%d PID: %d\n", n, getpid());
    sprintf(str, "%s %d", argv[0], n-1);
    system(str);
  }
  printf("End. PID=%d \n", getpid());
  return 1;
}
