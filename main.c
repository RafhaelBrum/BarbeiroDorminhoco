#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "main.h"

// Semáforos e variáveis globais
sem_t sem_cliente;          // Semáforo para contar clientes esperando
sem_t sem_barbeiro;         // Semáforo para controlar o barbeiro
pthread_mutex_t mutex;      // Mutex para proteger o acesso às cadeiras
int clientes_esperando = 0; // Contador de clientes esperando

void *barbeiro(void *arg)
{
    while (1)
    {
        // Protege o acesso à variável compartilhada
        pthread_mutex_lock(&mutex);
        if (clientes_esperando == 0)
        {
            printf("Barbeiro dormindo...\n\n");
        }
        pthread_mutex_unlock(&mutex);

        // Espera até que um cliente chegue
        sem_wait(&sem_cliente);

        // Protege o acesso à variável compartilhada
        pthread_mutex_lock(&mutex); // Trava o mutex
        clientes_esperando--;       // Decrementa o número de clientes esperando
        printf("Barbeiro atendendo um cliente. Clientes esperando: %d\n\n", clientes_esperando);
        pthread_mutex_unlock(&mutex); // Destrava o mutex

        // Barbeiro está atendendo o cliente
        sem_post(&sem_barbeiro);
        sleep(rand() % 3 + 1); // Simula o tempo de atendimento
    }
}

void *cliente(void *arg)
{
    Cliente *cli = (Cliente *)arg;

    pthread_mutex_lock(&mutex); // Trava o mutex
    if (clientes_esperando < NUM_CADEIRAS)
    {
        clientes_esperando++; // Incrementa o número de clientes esperando
        printf("Cliente %d chegou. Clientes esperando: %d\n\n", cli->id, clientes_esperando);

        // Acorda o barbeiro
        sem_post(&sem_cliente);

        // Destrava o mutex
        pthread_mutex_unlock(&mutex);

        // Espera ser atendido
        sem_wait(&sem_barbeiro);
        printf("Cliente %d atendido.\n\n", cli->id);
    }
    else
    {
        printf("Cliente %d indo embora. Nenhuma cadeira disponivel.\n\n", cli->id);
        pthread_mutex_unlock(&mutex); // Destrava o mutex
    }

    free(arg); // Libera a memória alocada para o ID do cliente
}

int main()
{
    pthread_t tid_barbeiro;
    pthread_t tid_cliente[20];

    // Inicializa os semáforos e o mutex
    sem_init(&sem_cliente, 0, 0);
    sem_init(&sem_barbeiro, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Cria a thread do barbeiro
    pthread_create(&tid_barbeiro, NULL, barbeiro, NULL);

    // Cria as threads dos clientes
    for (int i = 0; i < 20; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1; // Atribui um ID ao cliente
        pthread_create(&tid_cliente[i], NULL, cliente, id);
        sleep(rand() % 2 + 1); // Simula a chegada aleatória dos clientes
    }

    // Espera as threads dos clientes terminarem
    for (int i = 0; i < 20; i++)
    {
        pthread_join(tid_cliente[i], NULL);
    }

    // Cancela a thread do barbeiro
    pthread_cancel(tid_barbeiro);

    // Destrói os semáforos e o mutex
    sem_destroy(&sem_cliente);
    sem_destroy(&sem_barbeiro);
    pthread_mutex_destroy(&mutex);

    printf("Todos os clientes foram atendidos!");

    return 0;
}
