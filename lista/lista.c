#define _GNU_SOURCE // para o get_current_dir_name()
#include <unistd.h>
#include <sys/types.h> 
#include <dirent.h> // para as syscalls de diretorias (dirent = directory entry)
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char* diretoria;
    DIR* dirStream;
    struct dirent* dirEntry;
    int resultadoClose;
    char tipoFicheiro;

    // Argumentos a mais
    if (argc > 2)
    {
        write(STDERR_FILENO, "Argumentos a mais!\nSintaxe: ./lista nomeFicheiro\n", 49);
        exit(1);
    }
    // Diretoria não especificada (= usar a atual)
    else if (argc < 2) diretoria = get_current_dir_name();
    // Diretoria especificada (passada por argumento)
    else diretoria = argv[1];

    // Abrir diretoria
    dirStream = opendir(diretoria);
    if (dirStream == NULL) 
    { 
        perror("Erro na abertura da diretoria. A diretoria não existe.\nERRO"); 
        exit(1); 
    }

    // Percorrer pastas e ficheiros existentes na diretoria
    while ((dirEntry = readdir(dirStream)) != NULL)
    {
        if (dirEntry->d_type == 4) tipoFicheiro = 'D';
        else if (dirEntry->d_type == 8) tipoFicheiro = 'F';
        else tipoFicheiro = '0';
        
        if (tipoFicheiro != '0') printf("%c %s\n", tipoFicheiro, dirEntry->d_name);
    }

    // get_current_dir_name() usa malloc. É necessário libertar a memória.
    if (argc < 2) free(diretoria);

    // Fechar diretoria
    resultadoClose = closedir(dirStream);
    
    // Não houve erros
    return 0;
}
