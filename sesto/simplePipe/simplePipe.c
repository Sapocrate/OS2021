#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open

/*
il padre crea il figlio, riceve una sequenza di stringhe e termina.
Il figlio apre un file di testo, legge riga per riga, invia riga per riga al padre
e quando non c'è più niente da leggere termina.
Comunicazione padre-figlio tramite pipe

*/

int main(int argc, char const *argv[]) {
  int pipeFD[2]; //fd della pipe - si scrive su 1 e si legge su 0


  pipe(pipeFD);
  if(!fork()){
    //figlio
  }
  else{
    //padre
  }
  return 0;
}
