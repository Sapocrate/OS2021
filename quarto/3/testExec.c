#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali

int main(int argc, char const *argv[]) {
  char str[100];
  int i;

  for (i = 0; i < 2; i++) {
    if(fork()!=0){
      sprintf(str, "echo system with i=%d", i);
      system(str);
    }
    else{
      if(fork()==0){
        sprintf(str, "exec with i=%d", i);
        execlp("echo" , "myPgrm", str, NULL);
      }
    }
  }
  return 0;
}
