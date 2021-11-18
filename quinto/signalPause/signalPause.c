#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open

/*
Crea due figli, stampa i PID e attendi che entrambi terminino
aspettando il SIGCHILD.

-Il primo figlio legge i primi 50 bytes da file son1.txt, li
stampa a video e termina.
-Il secondo figlio legge i primi 50 byte dal file son2.txt e li
stampa a video, attende 5 secondi e termina



*/

//uso variabili globali per far sì che siano accessibili
//anche ai signal handler
int primoFiglio;
int secondoFiglio;

void sigHand(){
  if(primoFiglio==1){
    primoFiglio=0;
  }
  else {
    secondoFiglio=0;
  }
}

//scrivi sigHandler

int main(int argc, char const *argv[]) {
  int pid;
  primoFiglio=1;
  primoFiglio=1;
  pid= fork();

  if(pid==0){
    //primo figlio
    char f1Name[10]= "son1.txt";
    int f1 = open(f1Name, O_RDONLY);
    char buf1[50];
    int lett1;
    printf("PID primo figlio: %d\n", getpid());
    if(f1 == -1){
      printf("Error while opening son1.txt \n");
      return -1;
    }
    lett1=read(f1, buf1, 50);
    printf("bytes letti da son1.txt: %d\n", lett1);
    write (1 , buf1, 50);
    close(f1);
    return(0);
  }
  else{
    if(!fork()){
      //secondo figlio
      char f2Name[10]= "son2.txt";
      int f2 = open(f2Name, O_RDONLY);
      char buf2[50];
      int lett2;
      printf("PID secondo figlio: %d\n", getpid());
      if(f2 == -1){
        printf("Error while opening son2.txt \n");
        return -1;
      }
      lett2=read(f2, buf2, 50);
      printf("bytes letti da son2.txt: %d\n", lett2);
      write (1 , buf2, 50);
      close(f2);
      sleep(5); //sleep di 5 secondi
      //printf("fine secondo figlio\n" );
      return(0);
    }
    else{
      //padre
      signal(SIGCHLD, sigHand);
      // attende i segnali
      pause();
      printf("padre riprende\n");
      pause();
      if(!primoFiglio && !secondoFiglio){
        printf("handler triggered twice! father terminating\n");
      }
    }
  }
  return 0;
}
