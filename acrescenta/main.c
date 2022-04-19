#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{

  // Verificar se é recebido 3 argumentos, execução do programa, ficheiro de origem e ficheiro de destino
  if (argc > 3)
  {
    perror("Demasiados argumentos");
    exit(1);
  }
  if (argc < 3)
  {
    perror("Poucos Argumentos");
    exit(1);
  }

  // guardar o conteudo do 2º e 3º argumento, origem e destino
  char const *origin = argv[1];
  char const *destination = argv[2];

  // declaração das variaveis para o descritor de ficheiros de cada ficheiro
  int fdOrigin, fdDestination, readBytes, writtenBytes, closeOrigin, closeDestination;

  // array de char do tamanho de bufsiz para guardar o conteudo lido do ficheiro de origem
  char originContent[BUFSIZ];

  // abertura do ficheiro de origem verificando se este existe
  // caso não exista, é lançado um erro
  fdOrigin = open(origin, O_RDONLY);
  if (fdOrigin == -1)
  {
    
    perror("Ficheiro  inexistente");
    exit(1);
  }

  // abertura do ficheiro de destino verificando se este existe
  // caso não exista, é lançado um erro
  fdDestination = open(destination, O_WRONLY | O_APPEND);
  if (fdDestination == -1)
  {
    perror("Ficheiro de destino inexistente");
    exit(1);
  }

  do
  {
    // ler o ficheiro de origem e guardar o tamanho de bufsiz no array criado anteriormente
    // em caso de erro este é lançado
    readBytes = read(fdOrigin, originContent, BUFSIZ);

    if (readBytes < 0)
    {
      perror("Erro a ler o ficheiro de origem");
      exit(1);
    }

    // escrever no ficheiro de destino o array com o conteudo do lido ficheiro de origem
    // em caso de erro este é lançado
    writtenBytes = write(fdDestination, originContent, readBytes);
    if (writtenBytes < 0)
    {
      perror("Erro a escrever no ficheiro de destino");
      exit(1);
    }
  } while (readBytes > 0);

  // fechar os ficheiros abertos
  closeOrigin = close(fdOrigin);
  if (closeOrigin < 0)
  {
    perror("Erro a fechar o ficheiro de origem");
    exit(1);
  }
  closeDestination = close(fdDestination);
  if (closeOrigin < 0)
  {
    perror("Erro a fechar o ficheiro de destino");
    exit(1);
  }

  return 0;
}
