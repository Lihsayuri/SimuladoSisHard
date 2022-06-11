// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h> // importante para sinais
#include <fcntl.h> //importante para as flags de abrir documento
#include <string.h> //importante para strings

// Variável GLOBAL para armazenar o valor de PI aproximado
double pi = 0.0;

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one() {
    return (double)random()/(double)RAND_MAX;
}

// Função que calcula o valor de pi por simulação (Monte Carlo)
// Você não deve alterar esta função
double aproxima_pi() {
    long dentro = 0;
    long total_pontos = 0;

    double x,y,d;
    while (1) {
        x = random_zero_one();
        y = random_zero_one();
        d = x*x + y*y;
        if (d<=1) {
            dentro++;
        }
        total_pontos++;
        pi = 4.0 * ((double)dentro/(double)total_pontos);
        if (random_zero_one() < 0.008) {
            sleep(1);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------

// Exibir o PID do processo (10% da nota)

// Alterar o programa para que quando o processo receber um sinal SIGINT (o mesmo enviado quando o usuário
// aperta CTRL+C no terminal), dar um printf no valor atual da variável global pi e encerrar o processo (60% da
// nota)

// Além do item acima, ao receber SIGINT, salvar o valor atual da variável global pi em formato de texto em um
// arquivo pi.txt antes de encerrar o processo (30% da nota)

//-------------------------------------------------------------------------------------------------------------------

// Crie AQUI a função que exporta o valor de pi para um arquivo chamado pi.txt
// Esta função deve ser chamada pelo handler quando este for acionado

int conta_num_char(char string[]){
    int count = 0;  
      
    //Counts each character except space  
    for(int i = 0; i < strlen(string); i++) {  
        if(string[i] != '\n')  
            count++;  
    }  

    return count+1;
}

void exporta_pi_txt(int fd){
    char *log;
    log = malloc(sizeof(char)*10000);
    sprintf(log, "PI CALCULADO: %lf\n", pi);
    int bytes_written = write(fd, log, conta_num_char(log));
}

// Crie AQUI a função que será o handler do sinal

void sig_handler(int num) {
    printf("Você apertou Ctrl+C!\n");
    printf("O valor de pi no momento: %lf\n\n", pi);

    int fd = open("pi.txt", O_WRONLY | O_APPEND | O_CREAT, 0755);
    exporta_pi_txt(fd);

    struct sigaction s;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    s.sa_handler = SIG_DFL;
    sigaction(SIGINT, &s, NULL);

    kill(getpid(), SIGINT);
}

int main() {

    struct sigaction s;
    s.sa_handler = sig_handler; // aqui vai a função a ser executada
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;

    sigaction(SIGINT, &s, NULL);


    // Exiba o PID deste processo

    printf("Esse é o pid do processo: %d\n", getpid());

    // Registre AQUI seu handler para o sinal SIGINT!

    srand(time(NULL));
    aproxima_pi();

    return 0;
}


// gcc -Og -g q3.c -o q3