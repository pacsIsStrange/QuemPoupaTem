#include "lib.h"
#include <stdio.h>
void novoCliente(Clientes *cliente){
    int tipo;
    float saldo;
    long cpf;
    printf("Digite o nome do cliente:\n");
    scanf(" %99[^\n]", cliente->nome);
    printf("Digite o CPF do cliente:\n");
    scanf(" %ld", &cpf);
    printf("Digite a senha do cliente:\n");
    scanf(" %19[^\n]", cliente->senha);
    printf("Escolha o tipo da conta do cliente:\n1. Comum\n2. Plus\n");
    scanf("%d", &tipo);
    printf("Digite o saldo inicial da conta do cliente:\n");
    scanf("%f", &saldo);
};
int tamanho(Clientes *lc){
    FILE *strArquivo = fopen("ListaDeClientes.bin", "rb");
    int aux = 0;
    if (strArquivo) {
        while (fread(&lc[aux], sizeof(Clientes), 1, strArquivo) == 1){
            aux++;
        }
        fclose(strArquivo);
    }
    else {
        printf("\nERRO: Arquivo não encontrado.\n");
    }
    return aux;
};
void apagaCliente(int *tam, Clientes *lc, char cpfCliente);
int listarClientes(int tam, Clientes *lc){
  for(int i = 0; i < tam; i++){
    printf("\n--- CLIENTE NUMERO %d ---\n", i+1);
    printf("Nome: %s\n", lc[1].nome);
    printf("CPF: %s\n", lc[i].cpf);
    if (lc[i].tipo == 1){
      printf("Tipo: Comum");
    }
    else if(lc[1].tipo == 2){
      printf("Tipo: Plus");
    }
    else{
      printf("ERRO: tipo de conta invalido.");
    }
    printf("Saldo: %.2f", lc[i].saldo);
  }
};
int debito();
int deposito();
int extrato();
int transferencia();
void salvar(int tam, Clientes *lc){
    FILE *strArquivo = fopen("ListaDeClientes.bin", "wb");

    if (strArquivo){
        fwrite(lc, sizeof(Clientes), tam, strArquivo);
    }
    else{
        printf("\nERRO: Arquivo nao encontrado.\n");
    }
    fclose(strArquivo);
};
