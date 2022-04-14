/*a a) mostra ficheiro – Este comando deve apresentar no ecrã (todo) o conteúdo
do ficheiro indicado como parâmetro. Caso o ficheiro não exista, o comando
deve avisar o utilizador que o ficheiro não existe; */

#include <sys/types.h> // inclui definições de tipos de dados
#include <sys/stat.h> // define a estrutura dos dados devolvidos pela função stat()
#include <fcntl.h> // define os argumentos usados na função open()
#include <stdio.h> // para o perror() e para o BUFSIZ (tamanho standard para um buffer)
#include <unistd.h> // para as syscalls
#include <stdlib.h> // para usar o exit()

int main(int argc, char* argv[])
{
    // Argumentos a menos
    if (argc < 2) 
    {
        write(STDERR_FILENO, "Número de argumentos insuficiente!\nSintaxe: ./mostra nomeFicheiro\n", 67);
        exit(1);
    }
    // Argumentos a mais
    else if (argc > 2)
    {
        write(STDERR_FILENO, "Argumentos a mais!\nSintaxe: ./mostra nomeFicheiro\n", 50);
        exit(1);
    }

    int fd, bytesLidos, bytesEscritos, resultadoClose;
    char buffer[BUFSIZ];

    fd = open(argv[1], O_RDONLY); // abrir ficheiro filename em modo de leitura
    // Se houve algum erro na abertura do ficheiro (ex: ficheiro não existe)
    if (fd == -1) { perror("Erro na abertura do ficheiro. O ficheiro não existe.\nERRO"); exit(1); }

    // Enquanto não chegarmos ao fim do ficheiro (bytesLidos != 0)
    do 
    {
        // Ler do ficheiro
        bytesLidos = read(fd, buffer, BUFSIZ);
        // Se houve algum erro na leitura
        if (bytesLidos == -1) { perror("Erro na leitura.\nERRO"); exit(1); }
        
        // Escrever conteúdo lido na consola
        bytesEscritos = write(STDOUT_FILENO, buffer, bytesLidos);
        // Se houve algum erro na escrita
        if (bytesEscritos == -1) { perror("Erro na escrita.\nERRO"); exit(1); }
    } while (bytesLidos > 0);

    // Fechar ficheiro e fazer flush
    resultadoClose = close(fd);
    // Se houve algum erro a fechar o ficheiro
    if (resultadoClose == -1) {perror("Erro no fecho do ficheiro. ERRO"); exit(1); }

    // Não houve erros
    return 0; 
}
