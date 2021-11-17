#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
/*
input da linea di comando il PID del processo del programma precedente
(signal_kill) ed un comando:
"somma" ---> SIGUSR2 a <PID>
"differenza" ---> SIGUSR1 a <PID>
"fine" ---> SIGINT a <PID>

sostanzialmente sostituisce il dover usare kill su bash


SBAGLIATO: incompatibilita con codifica utf8 probabilmente,
ma al posto della system() era piu logico usare la kill().
Riscrivi il codice usando la
syscall kill()
*/

int main(int argc, char const *argv[]) {
  int pid =atoi(argv[1]);
  if(!strcmp(argv[2], "somma")){
    kill(pid, SIGUSR2);
    return 0;
  }

  if(!strcmp(argv[2], "fine")){
    kill(pid, SIGINT);
    return 0;
  }

  if(!strcmp(argv[2], "differenza")){
    kill(pid, SIGUSR1);
    return 0;
  }

  printf("input error! \n" );
  return 0;
}
