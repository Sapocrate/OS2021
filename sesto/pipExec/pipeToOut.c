#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open

/*


*/

#define STRING_LEN 50
  char numero[3];

void intToString(int number){
  sprintf(numero,"%d", number);
}

int main(int argc, char const *argv[]) {
  int pipeFD[2];
  char stringa[STRING_LEN];

  pipe(pipeFD); //0 per leggere, 1 per scrivere
  if(!fork()){
  //figlio che eseggue programma di input / conversione toupper
  intToString(pipeFD[1]);
  if(execl("./utp", "utp",numero, NULL)== -1){
    printf("exec error\n" );
    return 0;
  }
  }
  close(pipeFD[1]);
  read(pipeFD[0], stringa, STRING_LEN);
  execl("/bin/echo", "echo", stringa, NULL);
  return 0;
}
