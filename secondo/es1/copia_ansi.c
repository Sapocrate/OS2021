#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define buf_len 10

int main(int argc, char const *argv[]) {
  if (argc != 3){
    printf("arguments number error\n");
  }
  //rename the arguments
char *dest_path, *src_path;
dest_path=  argv[1];
src_path=  argv[2];

  int input_file= open(src_path , O_RDONLY);
  if(input_file==-1){
    printf("error while opening input file\n");
    return -1;
  }
  int output_file= open(dest_path , O_CREAT|O_WRONLY, S_IRWXU);
  if(output_file==-1){
    printf("error while opening output file\n");
    return -1;
  }

char buf[buf_len];
while (read(input_file, buf, buf_len)!=-1) {
  write(output_file, buf, buf_len);
}



  close(input_file);
  return 0;
}
