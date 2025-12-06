#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  
  char command[256];
  
  //REPL (Read-Eval-Print Loop).
  do{
    printf("$ ");
    
    // Flush after every print
    setbuf(stdout, NULL);

    if (fgets(command, sizeof(command), stdin) != NULL){
      //Usa strcspn para localizar a primeira ocorrência de \n e então substiuimos por \0, definindo assim o novo tamanho da string
      command[strcspn(command, "\n")] = '\0';

      if (strlen(command) > 0){
        printf("%s: command not found\n", command);
      }

      //caso exit, interrompe o loop e encerra.
      //strcmp retorna 0 quando a comparação é verdadeira, por isso precisar negar o resultado com !
      if (!strcmp("exit", command))
        return 0;

        
    };
  } while(1);

  return 0;
}
