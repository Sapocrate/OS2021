#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali

/*
il programma deve prendere da input due numeri interi, a e b ed aspettare
un segnale:
-Con il segnale SIGUSR2 deve effettuare la somma e stampare
-Con il segnale SIGUSR1 deve effettuare la differenza e stampare
-Con il segnale SIGINT deve terminare il processo

IN ESECUZIONE SU UN ALTRO TERMINALE MANDARE I SEGNALI
usr ~ $kill -SIGUSR2 3039
usr ~ $ kill -SIGUSR1 3039
usr ~ $ kill -SIGINT 3039
(N.B.: 3039 =pid stampato sul primo terminale)

hint: i signal handler non ricevono parametri, dunque si devono usare
delle variabili globali per far si che agiscano su a e b...
*/

int a;
int b;
int termina;

void sommaHandler(){
  printf("somma: %d\n", a+b);
}

void diffHandler(){
  printf("differnza: %d\n", a-b);
}

void stopHandler(){
  termina=1;
  printf("bye! \n" );
}

int main(int argc, char const *argv[]) {
  signal(SIGINT, stopHandler);
  signal(SIGUSR1, diffHandler);
  signal(SIGUSR2, sommaHandler);
  termina=0;
  printf("PROCESS PID: %d\n", getpid());
  printf("%s\n", "Please insert the first number: \n");
  scanf("%d", &a);
  printf("%s\n", "Please insert the second number: \n");
  scanf("%d", &b);
  while(!termina){

  }
  return 0;
}
