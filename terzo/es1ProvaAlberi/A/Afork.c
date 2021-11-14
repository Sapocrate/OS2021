#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int i;
  for(i=1; i<=2; i++){
    if(!fork())
    printf("%d\n", i);
  }
  printf("%d out if \n", i);
  return 0;
}
