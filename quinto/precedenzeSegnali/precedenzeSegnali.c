#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open

/*
il processo principale deve realizzare un grafo di
precedenza dei processi con:
primo stage S20
secondo stage S11 S21 S22
terzo stage S12 S23
quarto stage S13 S24
quinto stage S25

PROBLEMA
ho dovuto mettere dei sleep prima delle kill() perchè
altrimenti il processo che attendeva il segnale non andava in pause()
e la sincronizzazione saltava. Dunque questa impostazione di sincronizzazione
non è molto affidabile in caso di computazioni lunghe, bisogna integrare
con delle wait per i pid dei processi...


*/
//signal handler
 void sigHan(int sig){
  //printf("PID %d ha ricevuto segnale %d\n", getpid(), sig);
  printf("...\n");
}
void latoSx(int pidSig);
void latoDx(int pidSig);


int main(int argc, char const *argv[]) {
  //istanziazione robusta sigHandler, per SIGUSR1 e SIGUSR2
  if(signal(SIGUSR1, sigHan)== SIG_ERR || signal(SIGUSR2, sigHan)== SIG_ERR){
    printf("Signal handler error\n");
  }
  int pid1, pid2;
  printf("S20\n");
  //il primo processo continua l'esecuzione
  pid1=fork();
  if(!pid1){
    latoSx(getppid());
    return 0;
  }
  pid2=fork();
  if(!pid2){
    sleep(1);
    printf("S22\n");
    return 0;
  }
  latoDx(pid1);
  pause();
  sleep(1);
  printf("S25\n");
  return 0;
}

void latoSx(int pidSig){
  sleep(1);
  printf("S11\n");
  sleep(2);
  kill(pidSig, SIGUSR1);
  sleep(1);
  printf("S12\n");
  pause();
  printf("S13\n" );
  sleep(2);
  kill(pidSig, SIGUSR1);
}

void latoDx(int pidSig){
  sleep(1);
  printf("S21\n");
  pause();
  sleep(1);
  printf("S23\n");
  kill(pidSig, SIGUSR1);
  sleep(1);
  printf("S24\n");
}
