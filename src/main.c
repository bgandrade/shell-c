#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARGS 255
#define MAX_INPUT 1024

//-----------------------------------------------------------------

typedef int (*cmd_func_t)(char **args);

typedef struct
{
  char *cmd_name;
  cmd_func_t func;
} Command;

//-------------------------------------------------------------------

int cmd_help(char **args);
int cmd_echo(char **args);
int cmd_type(char **args);
int cmd_exit(char **args);
void parser(char *str, char **args);

//------------------------------------------------------------------

Command commands[] = {
    {"help", cmd_help},
    {"echo", cmd_echo},
    {"type", cmd_type},
    {"exit", cmd_exit},
    {NULL, NULL} // Sentinela para saber onde o array termina
};

//------------------------------------------------------------------

int main(int argc, char *argv[])
{

  char userCommand[MAX_INPUT];
  char *args[MAX_ARGS];

  int exit = 1;

  // REPL (Read-Eval-Print Loop).
  do
  {
    printf("$ ");

    // Flush after every print
    setbuf(stdout, NULL);

    if (fgets(userCommand, sizeof(userCommand), stdin) != NULL)
    {
      // Usa strcspn para localizar a primeira ocorrência de \n e então substituimos por \0, definindo assim o novo tamanho da string
      userCommand[strcspn(userCommand, "\n")] = '\0';

      parser(userCommand, args);

      Command *c = commands;
      while (c->cmd_name)
      {
        if (strcmp(c->cmd_name, args[0]) == 0)
        {
          exit = c->func(args);
          break;
        }
        c++;
      }

      // Se NULL não encontrou o comando solicitado
      if (c->cmd_name == NULL)
      {
        printf("%s: command not found\n", args[0]);
      }
    };
  } while (exit);

  return 0;
}

int cmd_exit(char **args)
{
  return 0; // Retorna 0 para sinalizar que o loop deve parar
}

int cmd_help(char **args)
{
  printf("Shell Demo - Comandos disponíveis: echo, exit, type\n");
  return 1;
}

int cmd_echo(char **args)
{
  args++; // pula o primeiro argumento, o nome do comando em sí

  while (*args)
  {
    printf("%s ", *args);
    args++;
  }
  printf("\n");
  return 1;
}

int cmd_type(char **args)
{
  Command *c = commands;
  while (c->cmd_name)
  {
    if (strcmp(c->cmd_name, args[1]) == 0)
    {
      printf("%s is a shell builtin\n", args[1]);
      break;
    }
    c++;
  }
  // Se NULL não encontrou o comando solicitado
  if (c->cmd_name == NULL)
  {
    printf("%s: not found\n", args[1]);
  }
  return 1;
}

void parser(char *str, char **args)
{
  bool in_arg = false;
  bool in_quotes = false;
  bool in_single_quotes = false;

  // loop por cada caractere da string
  while (*str != '\0')
  {
    // É um espaçço em branco
    if (*str == ' ')
    {
      if (in_arg)
      {
        *str = '\0'; // Insere um marcador de final de string
        in_arg = false;
      }
    }
    // Não é um espaço em branco
    else
    {
      // caso não esteja em argumento, inicia um
      if (!in_arg)
      {
        *args = str; // *args passa a apontar para o iniciodo argumento na string original
        args++;      // Avança o ponteiro para a próxima posição a ser preenchida no array
        in_arg = true;
      }
    }
    str++;
  }
  // insere um ponteiro nulo como sentilena para marcar o final do array.
  *args = NULL;
}
