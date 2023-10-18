#include "lib.h"
#include <stdio.h>
#include <string.h>

int main() {
  ListaDeClientes lc;

  char strArquivoClientes[] = "ListaDeClientes.bin";
  int codAux, opcao;

  codAux = carregar(&lc, strArquivoClientes);

  if (codAux != 0) {
    printf("lista de clientes nao carregada\n");
    lc.qtd = 0;
  }

  do {
    exibeMenu();
    scanf("%d", &opcao);

    if (opcao == 0) {
    } else if (opcao == 1) {
      codAux = novoCliente(&lc);
      if (codAux == 1)
        printf("ERRO: lista de clientes cheia, apague um cliente para cadastrar um novo.\n");
    } else if (opcao == 2) {
      codAux = apagaCliente(&lc);
      if (codAux == 1) {
        printf("ERRO: nao existem clientes para deletar\n");
      } else if (codAux == 2) {
        printf("ERRO: posicao do cliente invalida\n");
      }
    } else if (opcao == 3) {
      codAux = listarClientes(&lc);
      if (codAux == 1) {
        printf("ERRO: nao existem clientes para listar\n");
      }
    } else if (opcao == 4) {
      long long int cpf;
      float valor = 0;
      printf("Digite o CPF do cliente: \n");
      scanf("%lld", &cpf);
      printf("Digite o valor que sera debitado: \n");
      scanf("%f", &valor);
      codAux = debito(&lc, cpf, valor);
      if (codAux == 0) {
        printf("Operacao realizada com sucesso\n");
      }
      if (codAux == 1) {
        printf("ERRO: CPF nao encontrado ou senha incorreta\n");
      }
    } else if (opcao == 5) {
      long long int cpf;
      float valor = 0;
      printf("Digite o CPF do cliente: \n");
      scanf("%lld", &cpf);
      printf("Digite o valor que sera depositado: \n");
      scanf("%f", &valor);
      codAux = deposito(&lc, cpf, valor);
      if (codAux == 0) {
        printf("Operacao realizada com sucesso\n");
      }
      if (codAux == 1) {
        printf("ERRO: CPF nao encontrado\n");
      }
    } else if (opcao == 7){
      char senha[20];
      long long int cpfOrigem;
      long long int cpfDestino;
      float valor = 0;
      printf("Digite o valor que sera transferido: \n");
      scanf("%f", &valor);
      printf("Digite o CPF do cliente de destino: \n");
      scanf("%lli", &cpfDestino);
      printf("Digite o CPF do cliente de Origem: \n");
      scanf("%lli", &cpfOrigem);
      printf("Digite a senha do cliente de origem: \n");
      scanf("%s", senha);
      codAux = transferencia(&lc, cpfOrigem, cpfDestino, valor, senha);
      if (codAux == 0) {
        printf("Operacao realizada com sucesso\n");
      } else if(codAux == 1){
        printf("ERRO: CPF de origem e destino nao encontrados\n");
      } else if(codAux == 2){
        printf("ERRO: CPF de destino nao encontrado: \n");
      } else if (codAux == 3){
        printf("ERRO: CPF de origem nao encontrado ou senha incorreta: \n");
      } else if (codAux == 4){
        printf("ERRO: desconhecido\n");
      }  
    }
  } while (opcao != 0);

  codAux = salvar(&lc, strArquivoClientes);
  if (codAux != 0)
    printf("erro ao salvar alteracoes no arquivo");
}
