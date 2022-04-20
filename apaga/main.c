#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
  //Verifica o número de argumentos
    if (argc < 2)
    {
        write(STDERR_FILENO, "Número de argumentos insuficiente!\nSintaxe: ./mostra nomeFicheiro\n", 67);
        exit(1);
    }
    else if (argc > 2)
    {
        write(STDERR_FILENO, "Argumentos a mais!\nSintaxe: ./mostra nomeFicheiro\n", 50);
        exit(1);
    }

    // Tentar abrir o ficheiro
    char const *file = argv[1];

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
      perror("Erro na abertura do ficheiro!");
      exit(1);
    }
    else if(fd == 0)
    {
      perror("O ficheiro não existe no i-node!");
      exit(1);
    }

    // Dados do ficheiro, tentar ver se quem pretende eliminar é o dono
 



  return 0;
}
