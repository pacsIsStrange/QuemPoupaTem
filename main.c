#include <stdio.h>
#include "lib.h"

Clientes lc[1000];

int main() {
    int auxBool = 0, opcao, tam;
    tam = tamanho(lc);
    printf("PEDRO ALEXANDRE CUSTODIO SILVA - RA: 22.123.049-3\nLAURA DE SOUZA PARENTE - RA: 22.123.033-7\nGUILHERME MOREIRA COSTA - RA: 22.123.057-6\n");
    printf("--- PROJETO QuemPoupaTem ---\n");
    while (1) {
        printf("Escolha uma opcao:\n1.Novo Cliente \n2.Apaga cliente \n3.Listar clientes\n4.Debito\n5.Deposito\n6.Extrato\n7.Transferencia Entre Contas\n0.Sair\n");
        scanf("%d", &opcao);
        switch (opcao){
            case(1):
                if (tam == 1000){
                    printf("Limite de clientes atingido, delete um ou mais clientes para cadastrar um novo.\n");
                }
                printf("\n--- CADASTRAR CLIENTE ---\n");
                novoCliente(&lc[tam]);
                tam++;
                salvar(tam, lc);
                break;
            case(2):
                printf("\n--- REMOVER CLIENTE ---\n");
                break;
            case(3):
                printf("\n--- LISTAR CLIENTES ---\n");
                listarClientes(tam, lc);
                break;
            case(4):
                printf("\n--- DEBITO ---\n");
                break;
            case(5):
                printf("\n--- DEPOSITO ---\n");
                break;
            case(6):
                printf("\n--- EXTRATO ---\n");
                break;
            case(7):
                printf("\n--- TRANSFERENCIA ENTRE CONTAS ---\n");
                break;
            case(0):
                printf("\n--- SAINDO ---\n");
                salvar(tam, lc);
                auxBool = 1;
                break;
            default:
                printf("\nOPCAO INVALIDA. DIGITE UM NUMERO VALIDO.\n");
                break;
        }
        if (auxBool){
            break;
        }

    }
    salvar(tam, lc);
    return 0;
}
