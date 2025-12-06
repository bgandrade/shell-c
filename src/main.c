#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");

  char command[256];
  if (fgets(command, sizeof(command), stdin) != NULL){
    //Usa strcspn para localizar a primeira ocorrência de \n e então substiuimos por \0, definindo assim o novo tamanho da string
    command[strcspn(command, "\n")] = '\0';

    if (strlen(command) > 0){
      printf("%s: command not found", command);
    }
  };

  return 0;
}
