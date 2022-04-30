#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
  //Verifica o número de argumentos
    if (argc < 2)
    {
        write(STDERR_FILENO, "Número de argumentos insuficiente!\nSintaxe: ./apaga nomeFicheiro\n", 67);
        exit(1);
    }
    else if (argc > 2)
    {
        write(STDERR_FILENO, "Argumentos a mais!\nSintaxe: ./apaga nomeFicheiro\n", 50);
        exit(1);
    }

  int file;

  file = unlink(argv[1]);
  if (file == -1)
  {
    printf("Ocorreu um erro a abrir o ficheiro ou o ficheiro nao existe!");
  }

  return 0;
}
