#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open
#include <math.h>

/*
il programma deve valutare la seguente serie matematica
sommatoria 1->N-1(e^i / i)
il padre riceve N come input (10 come max) e crea N figli che calcolano il valore
dell'espressione dentro alla sommatoria, ed infine somma tutto per ottenere il valore
finale e stamparlo a scermo.

da debuggare e far funzionare
*/
#define MAX_NUM 10
#define MSG_LEN 20

double espressione(int i){
  double result= exp(i);
  result= result/i;
  return i;
}

void figlio(int num, int fd){
  double res=0.0;
  char msg[MSG_LEN];
  res= exp(num);
  res= res/num;
  sprintf(msg, "%lf", res);
  write(fd, msg, MSG_LEN);
}

 int main(int argc, char const *argv[]) {
  int N,i;
  double sum=0.0;
  double tmp;
  int pipeFD[2];

  printf("Insert a number (max %d): \n", MAX_NUM);
  scanf("%d\n", &N);
  if(N>MAX_NUM || N<=0){
    printf("input error!");
    return 0;
  }
  pipe(pipeFD); //0 per leggere, 1 per scrivere
  for(i=0; i<N; i++){
    if(!fork){
      //figlio
      figlio(i, pipeFD[1]);
    }
    else{
      //padre
      char msg[MSG_LEN];
      read(pipeFD[0], msg, MSG_LEN);
      sscanf(msg, "%lf", &tmp);
      sum += tmp;
    }
  }
  printf("%lf\n", sum);
  return 0;
}
