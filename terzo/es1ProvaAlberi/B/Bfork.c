#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int i;
  for(i=3; i>1; i--){
    if(fork())
      printf("%d\n", i);
  }
  printf("%d fuoriLoop\n", i);
  return 0;
}
