#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open
#include <pthread.h> //per i thread -> compilare gcc con -lpthread

/*
programma multithread che definisce una stringa di 20 caratteri - in globale
in modo che sia accessibile dal secondo thread - istanzi un thread di controllo.
Il main dovrà chiedere all'utente di inserire una stringa, che andrà a modificare
proprio quella globale, mentre il thread di controllo  dovrà analizzarne il contenuto
e, in caso corrisponda a "house", deve stampare "casa rilevata".
Se la stringa contiene "exit", l'esecuzione deve terminare.
*/

char msg[21];
//funzione di controllo del thread
void * control(void*args){
    while(strcmp(msg, "exit\n")!=0){
      if(!strcmp(msg, "house\n")){
        printf("casa rilevata\n");
      }
      sleep(1);
    }
    printf("fine esecuzione thread\n");
}

int main(int argc, char const *argv[]) {
  pthread_t tId;
  int tRet;
  tRet= pthread_create(&tId, NULL, &control, NULL);
  if(!tRet){
    printf("thread creato correttamente\n");
  }
  else{
    printf("errore creazione thread\n");
  }
  while(strcmp(msg, "exit\n")!=0){
    puts("inserire stringa\n");
    fgets(msg, 21, stdin);
    sleep(2);
  }
  pthread_join(tId, NULL);
  printf("fine esecuzione main\n");
  return 0;
}
