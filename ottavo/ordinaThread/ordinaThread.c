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
Programma concorrente che ordina i dati presenti in alcuni file.
il prgramma prende N parametri e crea N/2 thread.
ogni coppia di parametri è data da nome_file_input e nome_file_output
la prima riga di ogni file contiene un numero, ovvero il numero di righe successive
ogni riga conterrà un intero
il file andrà ordinato per ordine crescente
hint: ogni thread chiama le funzioni readFile, sort e writeFile

workflow:
creazione dei thread (in base ad argc)
readFile -> leggo prima riga, faccio malloc, leggo riga per riga -> completato
sort -> mergesort -> completato
writeFile -> apro file, scrivo riga per riga, chiudo file
*/

typedef struct {
  char* nome_file_input;
  char* nome_file_output;
  int numThread; //Serve perchè i thread possano accedere a lenArray
} param_thread;

void merge(int* v, int left, int center, int right);
//variabili globali
int* lenArray;

void sort(int * v, int sx, int dx){
  //implementazione mergesort
  int centro;
  if(sx<dx){
    centro= (sx+dx)/2;
    sort(v, sx, centro);
    sort(v, centro+1, dx);
    merge(v, sx, centro, dx);
  }

}

void merge(int* v, int left, int center, int right){
  int i=left;
  int j= center+1;
  int k=0;
  int *temp;
  temp= (int*) malloc(sizeof(int)* (right-left+1));
  while(i<=center && j<= right){
    if(v[i]<=v[j]){
      temp[k] = v[i];
      i++;
    }
    else{
      temp[k]= v[j];
      j++;
    }
    k++;
  }
  while(i<= center){
    temp[k] = v[i];
    i++;
    k++;
  }
  while(j<= right){
    temp[k] = v[j];
    j++;
    k++;
  }
  for(k=left; k<=right; k++){
    v[k]= temp[k-left];
  }
  free(temp);
}

int* readFile(char* input, int index){
  FILE* fp= fopen(input, "r");
  int * array;
  int len;
  if(fp==NULL){
    printf("errore nell'apertura del file %s\n", input);
    return NULL;
  }
  fscanf(fp, "%d" , &len);
  array= malloc(sizeof(int)* len);
  for (int i=0; i<len; i++){
    fscanf(fp, "%d", &array[i]);
    //printf("%d\n", array[i]); prova funzionamento lettura
  }
  lenArray[index] = len; //metto in globale la lunghezza del vettore del thread
  fclose(fp);
  return array;
}

void writeFile(int* array, int index, char* nomefile){
  int len= lenArray[index];
  FILE*fp;
  fp= fopen(nomefile, "w");
  if(fp==NULL){
    printf("errore apertura file thread %d\n", index);
    return;
  }
  fprintf(fp, "lunghezza: %d\n", len); //stampo la lunghezza del file
  for(int i=0; i<len; i++){
    fprintf(fp, "%d\n", array[i]);
  }
  fclose(fp);
}

void* threadFunction(void * args){
  //avendo puntatore a struct accederò ai dati con ->
  param_thread* param= (param_thread *) args;
  int* array;
  printf("input thread: %s\n", param->nome_file_input);
  printf("output thread: %s\n", param->nome_file_output);
  array= readFile(param->nome_file_input, param->numThread);
  sort(array, 0, lenArray[param->numThread]-1);
  writeFile(array, param->numThread, param->nome_file_output);
  free(array); //sta al thread liberare il vettore che è stato allocato dinamicamente nella readFile
}

int main(int argc, char const *argv[]) {
  int numParam= argc-1;
  int numThread;
  int argCount= 1;
  pthread_t *threadId;
  int *threadReturn;
  param_thread *param_array;

  if(numParam %2 != 0){
    printf("inserito numero errato di parametri\n");
    return 0;
  }
  numThread= numParam/2;
  //allocazione dinamica vettore TID, valori ritorno thread e array parametri e array globale lenArray
  threadId= (pthread_t*) malloc(sizeof(pthread_t)*numThread);
  threadReturn = (int *) malloc(sizeof(int) * numThread);
  param_array= (param_thread*) malloc(sizeof(param_thread)* numThread);
  lenArray= (int *) malloc(sizeof(int)* numThread);
  for(int i=0; i<numThread; i++){
    param_array[i].numThread= i;
    param_array[i].nome_file_input = malloc(sizeof(char)* strlen(argv[argCount]));
    strcpy( param_array[i].nome_file_input ,argv[argCount]);
    argCount++;
    param_array[i].nome_file_output = malloc(sizeof(char)* strlen(argv[argCount]));
    strcpy( param_array[i].nome_file_output ,argv[argCount]);
    argCount++;
    //ad ogni thread andrà passato il puntatore alla struct corrispondente ai sui parametri
    threadReturn[i] = pthread_create(&threadId[i], NULL, &threadFunction, &param_array[i]) ;

    //controllo errori creazione del thread
    if(threadReturn[i]!= 0){
      printf("errore nella creazione del thread %d\n", i);
      return -1;
    }

  }

  for (int i=0; i<numThread; i++){
    //aspetto che ogni thread abbia terminato l'esecuzione
    pthread_join(threadId[i], NULL);
    //libero le struct
    free(param_array[i].nome_file_input);
    free(param_array[i].nome_file_output);
  }
  printf("programma completato- thread terminati\n");
  //libero vettori allocati dinamicamente
  free(lenArray);
  free(param_array);
  free(threadId);
  free(threadReturn);
  return 0;
}
