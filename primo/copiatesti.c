#include "stdio.h"
#define MAXLINE 50

 int main(int argc, char const *argv[]) {
   //controllo che gli input siano solo 2
   if (argc != 3) {
     printf("%s %d\n", "arguments number error", argc );
     return -1;
   }
   FILE *src, *dest;
   char line[MAXLINE];
   src = fopen(argv[1], "r");
   dest = fopen(argv[2], "w");
   if (src == NULL || dest== NULL) {
     printf("error while opening files \n" );
     return -2;
   }
   //lettura e scrittura linea per linea
   while (fgets(line, MAXLINE, src)!=NULL){
     fputs(line, dest);
   }
   //chiusura dei files
   fclose(src);
   fclose(dest);
  return 0;
}
