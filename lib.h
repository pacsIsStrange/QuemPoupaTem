#include "lib.h"
#include <stdio.h>
int novoCliente(struct Clientes *cliente){
    int tipo;
    float saldo;
    printf("Digite o nome do cliente:\n");
    scanf(" %99[^\n]", cliente->nome);
    printf("Digite o CPF do cliente:\n");
    scanf(" %10[^\n]", cliente->cpf);
    printf("Digite a senha do cliente:\n");
    scanf(" %19[^\n]", cliente->senha);
    printf("Escolha o tipo da conta do cliente:\n1. Comum\n2. Plus\n");
    scanf("%d", &tipo);
    printf("Digite o saldo inicial da conta do cliente:\n");
    scanf("%.2f", &saldo);
};
int tamanho(struct Clientes *lc){
    FILE *strArquivo = fopen("ListaDeClientes", "rb");
    int aux = 0;
    if (strArquivo) {
        while (fread(&lc[aux], sizeof(struct Clientes), 1, strArquivo) == 1){
            aux++;
        }
        fclose(strArquivo);
    }
    else {
        printf("Arquivo não encontrado.");
    }
    return aux;
};
int apagaCliente();
int listarClientes();
int debito();
int deposito();
int extrato();
int transferencia();
int salvar();
