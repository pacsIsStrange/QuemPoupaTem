#include <stdio.h>
#include "lib.h"

struct Clientes lc[1000];

int main() {
    int auxBool = 0, opcao, tam;
    tam = tamanho(lc);

    while (1) {
        printf("Seja bem vindo ao programa Quem Poupa Tem!!\n");
        printf("Escolha uma opcao:\n1.Novo Cliente \n2.Apaga cliente \n3.Listar clientes\n4.Debito\n5.Deposito\n6.Extrato\n7.Transferencia Entre Contas\n0.Sair\n");
    }

    return 0;
}

