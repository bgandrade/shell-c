#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc < 2)
    return 1;
  
  printf("%s: command not found", argv[2]);

  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");

  return 0;
}
