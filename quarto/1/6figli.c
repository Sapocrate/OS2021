#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali

/*
Si scriva un programma C che genera 6 processi figli con le seguenti caratteristiche:
-tutti i 6 processi figli sono sempre in esecuzione
-i primi 3 generano continuamente un numero random e lo stampano in stdout
-i secondi 3 generano 50 numeri casuali e stampano il relativo quadrato su stdout
-ogni volta che un figlio termina deve essere sostituito con un figlio dello stesso tipo

PER TERMINARE PROCESSI CONTEMPORANEAMENTE USA KILLALL NOMEPROGRAMMA
es. < killall stampaRandom > uccide tutti i 3 processi che eseguono stampaRandom
*/

#define massimoRandom 100
int continua = 1;

//sistema segnale --> killall stampaRandom e termina esecuzione programmma
void handlerUsr1(){
  printf("Interruzione di tutti i figli e terminazione del processo padre...\n" );
  continua=0;
  if(!fork()){
    execlp( "killall" , "stampaRandom", NULL);
    printf("killall fallito\n" );
  }
  return;
}


int main(int argc, char const *argv[]) {

  //sistema terminazione automatica tramite segnali
  signal(SIGUSR1, handlerUsr1);

  int pid1, pid2, pid3;
  int pidWait;
  pid1 = fork();
  char lim[10];
  sprintf(lim, "%d", massimoRandom);
  char * argsPrint[] ={"./stampaRandom" , lim , "4" , NULL};
  if(pid1==0){
    printf("primo figlio prima exec %d\n", getpid());
    execvp("./stampaRandom" , argsPrint);
    printf("failed exec primo\n" );
    exit(0);
  }
  pid2 = fork();
  if(pid2==0){
    printf("secondo figlio prima exec %d\n", getpid());
    execvp("./stampaRandom" , argsPrint);
    printf("failed exec secondo\n" );
    exit(0);
  }
  pid3=fork();
  if(pid3==0){
    printf("terzo figlio prima exec %d\n", getpid());
    execvp("./stampaRandom" , argsPrint);
    printf("failed exec terzo\n" );
    exit(0);
  }

  //sistema di replacing dei figli terminati
  while(continua){
    pidWait =wait(NULL);
    printf("triggered replacing system\n");
    if(pidWait==pid1){
      printf("replacing primo figlio\n");
      if(!fork()){
        pid1=getpid();
        execvp("./stampaRandom" , argsPrint);
        printf("failed exec primo\n" );
      }
      exit(0);
    }
    if(pidWait==pid2){
      printf("replacing secondo figlio\n");
      if(!fork()){
        pid2=getpid();
        execvp("./stampaRandom" , argsPrint);
        printf("failed exec secondo\n" );
      }
      exit(0);
    }
    if(pidWait==pid3){
      printf("replacing terzo figlio\n");
      if(!fork()){
        pid3=getpid();
        execvp("./stampaRandom" , argsPrint);
        printf("failed exec terzo\n" );
      }
      exit(0);
    }
  }
  printf("father terminating %d\n",getpid() );
  return 0;
}
