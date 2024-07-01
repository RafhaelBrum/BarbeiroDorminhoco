#ifndef MAIN_H
#define MAIN_H

// Definição do número de cadeiras de espera
#define NUM_CADEIRAS 5

typedef struct cliente
{
    int id;
} Cliente;

// Função do barbeiro
void *barbeiro(void *arg);

// Função do cliente
void *cliente(void *arg);

#endif