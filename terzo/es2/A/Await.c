#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf

int main(int argc, char const *argv[]) {
  printf("A\n");
  int pid = fork();
  printf("B\n");
  if(pid){
    printf("father waiting\n");
    wait(NULL);
  }
  else{
    printf("C\n");
    sleep(5);
    exit(0);
  }
  return 0;
}
