#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int i;
  for (i=2; i>=1; i--){
    if(!fork())
      printf("%d\n", -i);
    else
      printf("%d\n", i);
  }
  return 0;
}
