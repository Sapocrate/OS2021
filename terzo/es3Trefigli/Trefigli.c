#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf

//processo padre che genera tre processi figli, i quali non
//generano nessun processo figlio
int main(int argc, char const *argv[]) {
  if (!fork()){
    //primo figlio
    printf("%s %d\n", "primo figlio, PID ", getpid());
  }
  else{
    if (!fork()) {
      //secondo figlio
      printf("%s %d\n", "secondo figlio, PID ", getpid());
    }
    else{
      if (!fork()) {
        //terzo figlio
        printf("%s %d\n", "terzo figlio, PID ", getpid());
      }
      else {
        printf("padre, PID %d\n", getpid());
      }
    }
  }
  return 0;
}
