#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf

int main(int argc, char const *argv[]) {
  int i, pid=0;
  for (i = 0; i < 3; i++) {
    if(pid==0){ //solo i processi appena generati genereranno a sua volta...
      printf("PID %d\n", getpid());
      pid= fork();
    }
  }
  if(pid==0) //per far stampare anche l-ultimo processo generato, che non cicla nel for
      printf("PID %d\n", getpid());
  printf("process end\n");
  return 0;
}
