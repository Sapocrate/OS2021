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

#define LINE_LEN 90

int main(int argc, char const *argv[]) {
  int pipeFD[2]; //fd della pipe - si scrive su 1 e si legge su 0


  pipe(pipeFD);
  if(!fork()){
    //figlio
    char line[LINE_LEN];
    FILE *fp= fopen("input.txt", "r");
    close(pipeFD[0]);
    if(fp==NULL){
      printf("error opening input.txt\n");
      return 0;
    }
    while (fgets(line, LINE_LEN, fp)!= NULL){
      write(pipeFD[1], line, LINE_LEN);
    }
    fclose(fp);
    close(pipeFD[1]);
    return 0;
  }
  else{
    //padre
    char in[LINE_LEN];
    close(pipeFD[1]);
    while(read(pipeFD[0], in, LINE_LEN)){
      printf("%s\n", in);
    }
    close(pipeFD[0]);
  }
  return 0;
}
