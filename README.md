**Projeto de Implantação Problemas Clássicos de IPC “Barbeiro Dorminhoco”** 
**Apresentação do Problema** 

**Descrição:** 

Imagine uma barbearia com um único barbeiro, uma cadeira de barbeiro e um número de cadeiras de espera (limitado). Os clientes chegam de forma aleatória para serem atendidos.  

Se o barbeiro está livre, ele imediatamente atende o cliente.  

Se o barbeiro está ocupado, o cliente se senta em uma das cadeiras de espera, se houver alguma disponível.  

Se todas as cadeiras de espera estiverem ocupadas, o cliente vai embora. 

O barbeiro, ao terminar de atender um cliente, verifica se há mais clientes esperando. Se houver, ele chama o próximo cliente da fila. Se não houver clientes esperando, ele dorme até que um novo cliente chegue e o acorde. 

**Objetivo:** 

Implementar uma solução para o problema do "Barbeiro Dorminhoco" em C utilizando Threads para simular o comportamento dos clientes e do barbeiro, garantindo a sincronização adequada entre eles. 

**Solução Proposta** 

1. **Threads:** 
- Uma thread para o barbeiro. 
- Várias threads para os clientes. 
2. **Recursos Compartilhados:** 
- Um mutex para proteger o acesso às cadeiras de espera. 
- Um semáforo para gerenciar os clientes esperando. 
- Um semáforo para gerenciar o barbeiro dormindo/acordado. 
3. **Estado dos Elementos:** 
- O barbeiro pode estar dormindo ou atendendo um cliente. 
- Os clientes podem estar esperando, sendo atendidos ou indo embora por falta de cadeira. 
