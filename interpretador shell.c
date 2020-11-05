/*Interpretador de Comandos (Shell) – Sistemas Operacionais

Felipe Santarosa
Giovana Pozzi Donadelli
Giancarlo Capovilla
Ian Albino
Rogerio Romualdo*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

    char comando[30];
    char *arg[3];
    int pid, erro=1;
    char senha[10];

    fflush(stdin);

    //pede a senha do sistema
    printf("Digite a senha: \n");
    fflush(stdin);
    fgets(senha, 10, stdin);

    //verifica se a senha é incorreta

    if(strncmp(senha, "fatecso", 7) != 0)
    {
    printf("Senha incorreta! \n");
    exit(1);
    }

    printf("Bem-vindo ao sistema de interpretador de comandos da fatec. Comandos: copiar, apagar, data, criar\n");

    //caso a senha esteja correta
    for( ; ; ){

erro = 1;

        printf("fatec> ");
        fgets(comando, 30, stdin);
fflush(stdin);

        argv[0]=strtok(comando, "");
        argv[1]=strtok(NULL, "");
        argv[2]=NULL;

        if(strncmp(argv[0], "sair", 4)==0){
        exit(0);
}

        if(strncmp(argv[0], "data", 4)==0){

 erro = 0;

 //aponta para o struct do time.h
 struct tm *data_hora_atual;
 time_t segundos;
 time(&segundos);

 //para converter de segundos para o tempo local utilizamos a função localtime
 data_hora_atual = localtime(&segundos);

 printf("\nData: %d/", data_hora_atual->tm_mday);//dia do mês
 printf("%d/",data_hora_atual->tm_mon+1); //mês
 printf("%d\n\n",data_hora_atual->tm_year+1900); //ano

        }

        if(strncmp(argv[0], "apagar", 6)==0){

erro = 0;

        char arquivo[30];
        printf("Digite o nome do arquivo: \n");
fflush(stdin);
        fgets(arquivo, 30, stdin);

//removendo o espaço do fim
char *pos;
if ((pos=strchr(arquivo, '\n')) != NULL)
*pos = '\0';

        //convertendo a string com uma aspa para aspas duplas, podendo assim chamar o arquivo com uma variável
char fileToOpen[strlen(arquivo) + 5];
strcpy(fileToOpen, arquivo);
strcat(fileToOpen, ".txt");

   FILE *arq1;

   arq1 = fopen(fileToOpen, "r");

   if (arq1 == NULL) {

     printf("erro ao abrir arquivo\n");

   }

   //deleta o arquivo
   if (unlink(fileToOpen) < 0){

     printf("erro no unlink\n");

   }

        }

        if(strncmp(argv[0], "copiar", 6)==0){

 erro = 0;

 FILE *arq1, *arq2;
 char texto[501], arquivo[30], copia[30], c;

 printf("Digite o nome do arquivo: \n");
 fflush(stdin);
 fgets(arquivo, 30, stdin);
 fflush(stdin);

 //removendo o espaço do fim da string
 char *pos;
 if ((pos=strchr(arquivo, '\n')) != NULL)
 *pos = '\0';


 printf("nome do arquivo e %s \n", arquivo);

 //convertendo a string com uma aspa para aspas duplas, podendo assim chamar o arquivo com uma variável

 char arquivoASerAberto[strlen(arquivo) + 5];
 // strlen(fileName)+5 porque é o tamanho do arquivo + ".txt" + char null

 strcpy(arquivoASerAberto, arquivo);
 // copia o valor para outra variável

 strcat(arquivoASerAberto, ".txt");
 // concatena o nome do arquivo com sua extenção .txt


 arq1 = fopen(arquivoASerAberto, "r");

 if (arq1 == NULL) {

   printf("o arquivo %s nao pode ser aberto\n", arquivo);

 }else{

     printf("Digite o nome que deseja para o arquivo:\n");
     fflush(stdin);
     fgets(copia, 30, stdin);
     fflush(stdin);


     //removendo o espaço do fim da string
     char *pos;
     if ((pos=strchr(copia, '\n')) != NULL)
     *pos = '\0';

     //convertendo a string com uma aspa para aspas duplas, podendo assim chamar o arquivo com uma variável
     char arquivoASerAberto2[strlen(copia) + 5];
     strcpy(arquivoASerAberto2, copia);
     strcat(arquivoASerAberto2, ".txt");

     //renomeia o arquivo para o nome desejado
     arq2 = fopen("replace.txt", "w");

     c = fgetc(arq1);

     if (arq1 != NULL && arq2 != NULL){

while (c != EOF){

fputc(c, arq2);
c = fgetc(arq1);

}

     }

     fclose(arq1);
     fclose(arq2);

     remove(arquivo);
     remove(copia);
     rename("replace.txt", arquivoASerAberto2);

     printf("arquivo copiado com sucesso!\n");

     }

}

if(strncmp(argv[0], "criar", 5)==0){

 erro = 0;

 FILE *arq1;
 char arquivo[30];

 printf("Digite o nome do arquivo: \n");
 fflush(stdin);
 fgets(arquivo, 30, stdin);
 fflush(stdin);

 //removendo o espaço do fim da string
 char *pos;
 if ((pos=strchr(arquivo, '\n')) != NULL)
 *pos = '\0';


 printf("nome do arquivo e %s \n", arquivo);


 //convertendo a string com uma aspa para aspas duplas, podendo assim chamar o arquivo com uma variável
 char arquivoASerAberto[strlen(arquivo) + 5];
 strcpy(arquivoASerAberto, arquivo);
 strcat(arquivoASerAberto, ".txt");



 arq1 = fopen(arquivoASerAberto, "r");

 //checa se o arquivo já existe e o cria logo em seguida
 if (arq1 == NULL) {

   arq1 = fopen( ("%s", arquivoASerAberto) ,"w");

 }else{

   printf("o arquivo ja existe\n");
   fclose(arq1);

 }

}

if(erro!=0){

     printf("COmando foi %s", argv[0]);
     printf("Comando invalido\n");

   }

    }

}
