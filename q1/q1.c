// Leia o PDF ou MD antes de iniciar este exercício!


// Faça os includes necessários aqui

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct semaforos{
    sem_t *s1;
    sem_t *s2;
    sem_t *s3;
    sem_t *s4;
} semaforos; 

void *thread1(void *args) {
    semaforos *arg = (semaforos *)args; 

    printf("A\n");

    sem_post(arg->s1);
    sem_post(arg->s1);
    sem_post(arg->s1);


    sem_wait(arg->s2);
    sem_wait(arg->s3);
    sem_wait(arg->s4);

    printf("E\n");

    return NULL;
}

void *thread2(void *args) {
    semaforos *arg = (semaforos *)args; 

    sem_wait(arg->s1);

    printf("B\n");

    sem_post(arg->s2);


    return NULL;
}

void *thread3(void *args) {
    semaforos *arg = (semaforos *)args; 

    sem_wait(arg->s1);

    printf("C\n");

    sem_post(arg->s3);


    return NULL;
}

void *thread4(void *args) {
    semaforos *arg = (semaforos *)args;

    sem_wait(arg->s1);

    printf("D\n");

    sem_post(arg->s4);

    return NULL;
}

int main(int argc, char *argv[]) {
    // primeiro, criar a lista de threads para fazer um malloc delas e usá-las na hora de criar as threads

    // void *lista_threads = malloc(sizeof(void*)*4);
    void *lista_threads[4] = {thread1, thread2, thread3, thread4};

    // depois criar os semáforos e alocar memoria pra eles

    semaforos *s = malloc(sizeof(semaforos));

    s->s1 = malloc(sizeof(sem_t));
    s->s2 = malloc(sizeof(sem_t));
    s->s3 = malloc(sizeof(sem_t));
    s->s4 = malloc(sizeof(sem_t));

    // depois criar lista de tids, alocar espaço pra elas

    pthread_t *lista_tids = malloc(sizeof(pthread_t)*4);

    // depois inicializar os semaforos em 0

    sem_init(s->s1, 0, 0); // segundo valor é 0 porque quero compartilhar os semáforos e só para usar dentro do processo
    sem_init(s->s2, 0, 0);
    sem_init(s->s3, 0, 0);
    sem_init(s->s4, 0, 0);

    for (int i = 0; i < 4; i++){
        // guardar o tid, null, passa a thread, passa o semaforo (args)
        pthread_create(&lista_tids[i], NULL, lista_threads[i], s);
    }

    for (int i = 0; i < 4; i++){
        pthread_join(lista_tids[i], NULL);
    }



    sem_destroy(s->s1);
    sem_destroy(s->s2);
    sem_destroy(s->s3);
    sem_destroy(s->s4);


    // Crie TODAS as threads em um laço. Voce deve utilizar semaforos para sincronizacao.


    // Espere por TODAS as threads
    // gcc -Og -g q1.c -o q1 -pthread
    
    return 0;
}