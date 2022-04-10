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

int openFiles(char const *originPath, char const *destinationPath, int *fileDescriptors)
{

  fileDescriptors[0] = open(originPath, O_RDONLY);
  if (fileDescriptors[0] == -1)
  {
    perror("Erro na abertura do ficheiro de origem");
    exit(-1);
  }

  fileDescriptors[1] = open(destinationPath, O_WRONLY | O_APPEND);
  if (fileDescriptors[1] == -1)
  {
    perror("Erro na abertura do ficheiro de destino");
    exit(-1);
  }
  return 1;
}

int append(int originFd, int destinationFd, int sizeOfOrigin)
{

  char originContent[sizeOfOrigin];
  int readBytes = read(originFd, originContent, sizeOfOrigin);
  if (readBytes < 0)
  {
    perror("Erro a ler o ficheiro de origem");
    exit(-1);
  }

  int written = write(destinationFd, originContent, sizeOfOrigin);
  if (written < 0)
  {
    perror("Erro a escrever no ficheiro de destino");
    exit(-1);
  }

  return 1;
}

int closeFiles(int originFd, int destinationFd)
{
  close(originFd);
  close(destinationFd);
  return 1;
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
  int fileDescriptors[2];

  openFiles(origin, destination, fileDescriptors);

  append(fileDescriptors[0], fileDescriptors[1], getFileSize(origin));

  closeFiles(fileDescriptors[0], fileDescriptors[1]);

  return 0;
}
