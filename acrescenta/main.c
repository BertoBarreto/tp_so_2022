#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

/*
Função que recebe o ficheiro de origem e devolve o tamanho
Esta função através do stat consegue obter o tamanho do ficheiro em bytes devolvendo então
*/
long int getFileSize(char const *origin)
{
  struct stat fileStat;
  stat(origin, &fileStat);

  return (long int)fileStat.st_size;
}

int main(int argc, char const *argv[])
{

  // Verificar se é recebido 3 argumentos, execução do programa, ficheiro de origem e ficheiro de destino
  if (argc > 3 || argc < 3)
  {
    perror("Argumentos invalidos");
    exit(1);
  }

  // guardar o conteudo do 2º e 3º argumento, origem e destino
  char const *origin = argv[1];
  char const *destination = argv[2];

  // declaração das variaveis para o descritor de ficheiros de cada ficheiro
  int fdOrigin, fdDestination;

  // abertura do ficheiro de origem verificando se este existe
  // caso não exista, é lançado um erro
  fdOrigin = open(origin, O_RDONLY);
  if (fdOrigin == -1)
  {
    perror("Erro na abertura do ficheiro de origem");
    exit(-1);
  }

  // abertura do ficheiro de destino verificando se este existe
  // caso não exista, é lançado um erro
  fdDestination = open(destination, O_WRONLY | O_APPEND);
  if (fdDestination == -1)
  {
    perror("Erro na abertura do ficheiro de destino");
    exit(-1);
  }

  // obter o tamanho do ficheiro de origem em bytes
  long int sizeOfOrigin = getFileSize(origin);

  // criar um array de char do tamanho do ficheiro de origem para guardar o conteudo do ficheiro de origem
  // visto que 1 char = 1 byte então assim é possivel saber o numero de caracteres para guardar
  char originContent[sizeOfOrigin];

  // ler o ficheiro de origem e guardar o seu conteudo no array criado anteriormente
  // em caso de erro este é lançado
  int readBytes = read(fdOrigin, originContent, sizeOfOrigin);
  if (readBytes < 0)
  {
    perror("Erro a ler o ficheiro de origem");
    exit(-1);
  }

  // escrever no ficheiro de destino o array com o conteudo do ficheiro de origem
  // em caso de erro este é lançado
  int written = write(fdDestination, originContent, sizeOfOrigin);
  if (written < 0)
  {
    perror("Erro a escrever no ficheiro de destino");
    exit(-1);
  }

  // fechar os ficheiros abertos
  close(fdOrigin);
  close(fdDestination);

  return 0;
}
