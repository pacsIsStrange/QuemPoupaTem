#ifndef QUEMPOUPATEM_LIB_H
#define QUEMPOUPATEM_LIB_H

 struct Clientes{
    char nome[100];
    char cpf[11];
    int tipo;
    float saldo;
    char senha[20];
};
int tamanho(struct Clientes *lc);
int novoCliente();
int apagaCliente();
int listarClientes();
int debito();
int deposito();
int extrato();
int transferencia();
int salvar();

#endif //QUEMPOUPATEM_LIB_H
