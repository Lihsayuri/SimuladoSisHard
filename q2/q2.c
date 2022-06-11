// Leia o PDF ou MD antes de iniciar este exercício!

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

// ./q2 <origem> <destino> <valor>


int main(int argc, char *argv[]){
    int ret;
    int wstatus;
    char *retorno_funcao;

    if (argc < 4){
        ret = -1;
        printf("Erro! Quantidade de parametros insuficiente\n");
        printf("Exemplo de uso:\n");
        printf("./siscoin ab134d4 d8b0a9e 109.75\n");
        return ret;
    }

    do {
        // Construa a chamada do executavel siscoin. Veja enunciado.
        pid_t filho = fork();

        if (filho == 0)
        {
            char *args[] = {"./siscoin", argv[1], argv[2], argv[3]};
            execvp("./siscoin", args);
        } else{
            wait(&wstatus);

            ret = (int) WEXITSTATUS(wstatus); // retorno do filho

            // printf("Esse é o retorno: %s\n", strsignal(ret));

            if (ret == 255){
                ret = -1;
            }

            // printf("Esse é o retorno: %d\n", ret);

            if (ret == -1){
                printf("Erro! Quantidade de parametros insuficiente\n");
                printf("Exemplo de uso:\n");
                printf("./siscoin ab134d4 d8b0a9e 109.75\n");
            } else if (ret >= 1 && ret <= 4){
                printf("Falha na rede!\n");
            } else {
                printf("Transferência realizada!\n");
            }

        }

        // No pai, espere e trate o resultado

        // DICA: ao atribuir o return do siscoin, faça casting para (char)

    } while (ret > 0); // Repita enquanto houver falha. 
                       // Para se tem problema com o valor ou a qtde de parâmetros
                       // Esta validação está sendo feita em siscoin

    return 0;
}

//gcc -Og -g q2.c -o q2
// man 7 signal
// man 2 wait