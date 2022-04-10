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

  long int originSize = getFileSize(origin);
  char originContent[originSize];
  int readBytes = read(fdOrigin, originContent, originSize);
  if (readBytes < 0)
  {
    perror("não foi possivel ler o ficheiro de destino");
    exit(-1);
  }

  int written = write(fdDestination, originContent, originSize);
  if (written < 0)
  {
    perror("não foi possivel escrever no destino");
    exit(-1);
  }

  close(fdOrigin);
  close(fdDestination);

  return 0;
}
