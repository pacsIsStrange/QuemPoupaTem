#ifndef QUEMPOUPATEM_LIB_H
#define QUEMPOUPATEM_LIB_H

 typedef struct{
    char nome[100];
    long cpf;
    int tipo;
    float saldo;
    char senha[20];
} Clientes;
int tamanho(Clientes *lc);
void novoCliente(Clientes *cliente);
void apagaCliente(int *tam, Clientes *lc, char cpfCliente);
int listarClientes(int tam, Clientes *lc);
int debito();
int deposito();
int extrato();
int transferencia();
void salvar(int tam, Clientes *lc);

#endif //QUEMPOUPATEM_LIB_H
