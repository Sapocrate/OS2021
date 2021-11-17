#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali

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

//scrivi sigHandler

int main(int argc, char const *argv[]) {
  int pid;
  pid= fork();

  if(pid==0){
    //primo figlio
    char f1Name[10]= "son1.txt";
    int f1 = open(f1Name, O_RDONLY);
    //scrivi read e write
  }
  else{
    if(!fork()){
      //secondo figlio

      //apri file, read, write e wait 5 sec
    }
    else{
      //padre
      //ciclo per attendere i segnali 
    }
  }
  return 0;
}
