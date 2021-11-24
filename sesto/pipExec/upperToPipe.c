#include <sys/types.h> //per il tipo pid
#include <sys/wait.h> //per la wait
#include <stdlib.h> //per la exit e la system
#include <unistd.h> //per il fork
#include <stdio.h> //per il printf
#include <string.h> //tools per le stringhe
#include <signal.h> //libreria per i segnali
#include <fcntl.h> //per open
#include <ctype.h> // per isupper, islower ecc.

/*
  riceve una stringa dallo stdin e stampa in uscita la stringa maiuscola
  sulla pipe, il cui fd passato da parametro
*/
#define STRING_LEN 50

void toUpper(char * string){
  int i;
  for(i=0; i<STRING_LEN && string[i]!= '\0'; i++){
    if(islower(string[i])){
      string[i]= toupper(string[i]);
    }
  }
}

int main(int argc, char const *argv[]) {
  int pipeFD;
  char line[STRING_LEN];
  printf("%s\n", argv[1]);
  pipeFD= atoi(argv[1]);
  printf("si inserirsca una stringa di max %d\n",STRING_LEN );
  scanf("%s",line );
  toUpper(line);
  if(write(pipeFD, line, STRING_LEN)==-1){
    printf("pipe error\n");
  }
  return 0;
}
