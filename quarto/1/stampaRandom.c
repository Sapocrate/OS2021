#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali

int main(int argc, char const *argv[]) {
  srand(2403); //inizializzo seed random
  int massimoRandom= atoi(argv[1]); //maxrand passato tramite parametro
  int tempo = atoi(argv[2]); //tempo di attesa passato tramite param
  int n = rand();
  // mappo da zero a cento
  n= n%massimoRandom;
  printf("PID processo figlio dopo exec: %d\n", getpid());
  while(1){
    fprintf(stdout, "%d\n", n);
    n= rand()%massimoRandom;
    sleep(tempo);
  }
  return 0;
}
