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
Il programma crea due thread, che quando vengono generati stampano
n-esimo thread creato, dopodichè stampa elaborazione n-esimo thread, aspetta 5 secondi
 e quando termina stampa il n-esimo thread termina
*/

//prima thread function
void* prima(void * args){
  printf("elaborazione primo thread\n");
  sleep(5);
  printf("primo thread terminato\n");
  pthread_exit(NULL);
}

//seconda thread function
void* seconda(void * args){
  printf("elaborazione secondo thread\n");
  sleep(5);
  printf("secondo thread terminato\n");
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t tId1, tId2;
  int tReturn1, tReturn2;
  tReturn1= pthread_create(&tId1, NULL, &prima, NULL); //niente argomento thread e argomento funzioni
  if(!tReturn1){
    printf("primo thread creato correttamente!\n");
  }
  else{
    printf("errore generazione primo thread\n");
  }
  tReturn2= pthread_create(&tId2, NULL, &seconda, NULL); //niente argomento thread e argomento funzioni
  if(!tReturn2){
    printf("secondo thread creato correttamente!\n");
  }
  else{
    printf("errore generazione secondo thread\n");
  }
  pthread_join(tId1, NULL); //aspetto l'esecuzione del primo thread
  pthread_join(tId2, NULL); //aspetto l'esecuzione del secondo thread
  printf("fine nel main\n" );
  return 0;
}
