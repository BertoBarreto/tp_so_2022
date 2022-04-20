#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
  int fd, len, contadorLinhas = 0, fecharFicheiro;
  char content[BUFSIZ];

  // vai abrir o ficheiro
  fd = open(argv[1], O_RDONLY);

  // vai verificar se o ficheiro existe, caso contrário dá erro
  if (fd == -1)
  {
    perror("Ficheiro não existe");
    exit(1);
  }

  // vai percorrer o ficheiro e descobrir o tamanho dele
  //  guarda na variavel len
  //  de seguida vai percorrer todos os caracteres e sempre que encontra \n
  // entao vai acrescentar ao contador de linhas mais 1
  len = read(fd, content, sizeof(content));
  for (int i = 0; i < len; i++)
  {
    if (content[i] == "\n")
    {
      contadorLinhas++;
    }
  }

  // por fim fechamos o fiicheiro
  fecharFicheiro = close(fd);
  // caso haja erro então devolvemos uma mensagemcom o erro
  if (fecharFicheiro == -1)
  {
    perror("Não foi possivel fechar o ficheiro");
    exit(1);
  }

  return 0;
}
