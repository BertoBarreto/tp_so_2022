#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <string.h>

/*
Esta função permite obter o tipo de ficheiro a partir do valor st_mode do stat
Utilizando as funções definidas é possivel verificar o tipo de ficheiro através do st_mode
*/
char *getFileType(mode_t st_mode)
{

  // verificar se é bloco
  if (S_ISBLK(st_mode))
  {
    return "Bloco";
  }
  // verificar se é uma diretoria
  else if (S_ISDIR(st_mode))
  {
    return "Diretoria";
  }
  // verificar se é um link
  else if (S_ISLNK(st_mode))
  {
    return "Link";
  }
  // verificar se é um ficheiro regular
  else if (S_ISREG(st_mode))
  {
    return "Regular";
  }

  return "Indefinido";
}

/*
  Esta função permite imprimir na consola uma string
  Utilizando a função write é escrito para o stdout a string recebida
*/
int print(char *string)
{
  int wr = write(STDOUT_FILENO, string, strlen(string));
  if (wr < 0)
  {
    perror("Erro a escrever na consola");
  }
  return 1;
}

int main(int argc, char const *argv[])
{
  // Verificar se é recebido apenas os argumentos necessários
  if (argc > 2 || argc < 2)
  {
    perror("Argumentos invalidos");
    exit(-1);
  }

  // verificar se o ficheiro existe
  if (open(argv[1], O_RDONLY) < 0)
  {
    perror("Erro no ficheiro");
    exit(-1);
  }

  // obter o stat do ficheiro
  struct stat fileStat;
  stat(argv[1], &fileStat);

  // obter informações sobre o utilizador através do id de utilizador obtido com o stat do ficheiro
  struct passwd *userInfo = getpwuid(fileStat.st_uid);
  // obter a string com o tipo de ficheiro
  char *type = getFileType(fileStat.st_mode);

  // obter as datas convertidas de unix para formato data
  char *cDate = ctime(&fileStat.st_ctime);
  char *mDate = ctime(&fileStat.st_mtime);
  char *aDate = ctime(&fileStat.st_atime);

  // tamanho da string de info do tipo de ficheiro
  long int fileTypeSize = strlen(type) + 20;

  // tamanho da string de info do inode
  long int iNodeSize = sizeof(fileStat.st_ino) + 9;

  // tamanho da string de info do dono do ficheiro
  long int ownerSize = sizeof(userInfo->pw_name) + 19;

  // tamanho da data sendo 24 o tamanho da data e o resto o tamanho da string de info
  long int cDateSize = strlen(cDate) + 20;
  long int mDateSize = strlen(cDate) + 24;
  long int aDateSize = strlen(cDate) + 25;

  // arrays para guardar a strings de info
  char fileTypeString[fileTypeSize], iNodeString[iNodeSize], ownerString[ownerSize],
      cDateString[cDateSize], mDateString[mDateSize], aDateString[aDateSize];

  // formatação das strings com os dados necessários
  snprintf(fileTypeString, fileTypeSize, "Tipo de ficheiro: %s\n", type);
  snprintf(iNodeString, iNodeSize, "I-Node: %ld\n", fileStat.st_ino);
  snprintf(ownerString, ownerSize, "Dono do ficheiro: %s\n", userInfo->pw_name);
  snprintf(cDateString, cDateSize, "Data de criação: %s", cDate);
  snprintf(mDateString, mDateSize, "Data de modificação: %s", mDate);
  snprintf(aDateString, aDateSize, "Data da ultima leitura: %s", aDate);

  // imprimir os dados na consola
  print(fileTypeString);
  print(iNodeString);
  print(ownerString);
  print(cDateString);
  print(mDateString);
  print(aDateString);

  return 0;
}
