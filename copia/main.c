#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //para o strcat

int main(int argc, char *argv[])
{   
    char* nomeFicheiroCopia;

    // Verificar se é recebido 2 argumentos, execução do programa (./copia) ficheiro de origem
    if (argc > 2)
    {
        write(STDERR_FILENO, "Muitos Argumentos!\nSintaxe: ./copia origem \n", 45);
        exit(1);
    }
    if (argc < 2)
    {
        write(STDERR_FILENO, "Poucos Argumentos!\nSintaxe: ./copia origem \n", 45);
        exit(1);
    }

    int fd, fd2, bytesLidos, bytesEscritos, resultadoClose, resultadoClose2;
    char buffer[BUFSIZ];

    // abertura do ficheiro, verificando em seguida se este existe
    fd = open(argv[1], O_RDONLY);
    // se acontecer algum erro como o ficheiro não existir, vai ser retornado -1 (erro)
    if(fd == -1) { perror("ERRO!!! O ficheiro não existe."); exit(1); }

    // o strcat junta o 2º argumento no fim do 1º
    nomeFicheiroCopia = strcat(argv[1], ".copia");

    // abertura ou criação do ficheiro onde vamos copiar o conteúdo do original
    fd2 = open(nomeFicheiroCopia, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
    if(fd == -1) { perror("ERRO!!! O ficheiro não existe."); exit(1); }

    // ciclo que irá ser útil caso o ficheiro tenho um tamanho muito grande
    do
    {
        // vamos ler o conteúdo do ficheiro que abrimos (se este existir)
        bytesLidos = read(fd, buffer, BUFSIZ);
        // se acontecer algum erro durante a leitura, o retorno vai ser -1
        if(bytesLidos == -1) { perror("ERRO!!! Não foi possível ler o ficheiro."); exit(1); }

        // passar para dentro do ficheiro.copia o conteúdo do ficheiro original
        bytesEscritos = write(fd2, buffer, bytesLidos);
        if(bytesEscritos == -1) { perror("ERRO!!! Não foi possível escrever."); exit(1); }

    } while (bytesLidos > 0);
    
    // fechar os ficheiros
    resultadoClose = close(fd);
    resultadoClose2 = close(fd2);
    // se acontecer algum erro ao fechar os ficheiros
    if(resultadoClose == -1) { perror("ERRO!!! Não foi possível fechar o ficheiro."); exit(1); }
    if(resultadoClose2 == -1) { perror("ERRO!!! Não foi possível fechar o ficheiro."); exit(1); }

    // Caso não haja erros
    return 0;  
}