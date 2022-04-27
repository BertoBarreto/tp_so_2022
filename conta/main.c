#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int fd, len, contadorLinhas = 0, fecharFicheiro;
  char content[BUFSIZ];

  // vai abrir o ficheiro
  fd = open(argv[1], O_RDONLY);

  // vai verificar se o ficheiro existe, caso contrário dá erro
  if (fd == -1)
  {
    write(STDERR_FILENO, "Ficheiro não existe\n", 22);
    exit(1);
  }

  // vai percorrer o ficheiro e descobrir o tamanho dele
  //  guarda na variavel len
  //  de seguida vai percorrer todos os caracteres e sempre que encontra \n
  // entao vai acrescentar ao contador de linhas mais 1

  do
  {
    len = read(fd, content, BUFSIZ);

    for (int i = 0; i < len; i++)
    {
      if (content[i] == '\n')
      {
        contadorLinhas++;
      }
    }
  } while (len > 0);

  char mostraResultado[32 + sizeof(contadorLinhas)];
  // função write serve para apresentar ao utilizador quantas linhas tem o ficheiro
  snprintf(mostraResultado, 32 + sizeof(contadorLinhas), "O ficheiro contém: %d linhas \n", contadorLinhas);
  write(STDOUT_FILENO, mostraResultado, strlen(mostraResultado));
  // por fim fechamos o ficheiro
  fecharFicheiro = close(fd);
  // caso haja erro então devolvemos uma mensagemcom o erro
  if (fecharFicheiro == -1)
  {
    write(STDERR_FILENO, "Não foi possivel fechar o ficheiro\n", 37);
    exit(1);
  }

  return 0;
}
