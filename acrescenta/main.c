#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

long int getFileSize(char const *origin)
{
  struct stat fileStat;
  stat(origin, &fileStat);

  return (long int)fileStat.st_size;
}
// TODO:Documentar o codigo
int main(int argc, char const *argv[])
{
  if (argc > 3 || argc < 3)
  {
    perror("Argumentos invalidos");
    exit(1);
  }
  char const *origin = argv[1];
  char const *destination = argv[2];

  int fdOrigin, fdDestination;

  fdOrigin = open(origin, O_RDONLY);
  if (fdOrigin == -1)
  {
    perror("Erro na abertura do ficheiro de origem");
    exit(-1);
  }

  fdDestination = open(destination, O_WRONLY | O_APPEND);
  if (fdDestination == -1)
  {
    perror("Erro na abertura do ficheiro de destino");
    exit(-1);
  }

  long int sizeOfOrigin = getFileSize(origin);
  char originContent[sizeOfOrigin];
  int readBytes = read(fdOrigin, originContent, sizeOfOrigin);
  if (readBytes < 0)
  {
    perror("Erro a ler o ficheiro de origem");
    exit(-1);
  }

  int written = write(fdDestination, originContent, sizeOfOrigin);
  if (written < 0)
  {
    perror("Erro a escrever no ficheiro de destino");
    exit(-1);
  }

  close(fdOrigin);
  close(fdDestination);

  return 0;
}
