#include "lib.h"
#include <stdio.h>

int main() {
  ListaDeClientes lc;

  char strArquivoClientes[] = "ListaDeClientes.bin";
  int codAux, opcao;

  codAux = carregar(&lc, strArquivoClientes);

  if (codAux != 0) {
    printf("lista de tarefas nao carregada");
    lc.qtd = 0;
  }

  do {
    exibeMenu();
    scanf("%d", &opcao);

    if (opcao == 0) {
    } else if (opcao == 1) {
      codAux = novoCliente(&lc);
      if (codAux == 1)
        printf("ERRO: lista de clientes cheia, apague um cliente para "
               "cadastrar um novo.\n");
    } else if (opcao == 2) {
      codAux = apagaCliente(&lc);
      if (codAux == 1) {
        printf("ERRO: nao existem tarefas para deletar\n");
      } else if (codAux == 2) {
        printf("ERRO: posicao da tarefa invalida\n");
      }
    } else if (opcao == 3) {
      codAux = listarClientes(&lc);
      if (codAux == 1) {
        printf("erro ao listar tarefas: nao existem tarefas para listar\n");
      }
    } else if (opcao == 4) {
      long long int cpf;
      float valor = 0;
      char senha;
      printf("Digite o CPF do cliente: \n");
      scanf("%lld", &cpf);
      printf("Digite a senha do cliente: \n");
      scanf("%s", &senha);
      printf("Digite o valor que sera debitado: \n");
      scanf("%f", &valor);
      codAux = debito(&lc, cpf, &senha, valor);
      if (codAux == 0) {
        printf("Operacao realizada com sucesso\n");
      }
      if (codAux == 1) {
        printf("ERRO: CPF nao encontrado\n");
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
        printf("Operacao realizada com sucesso");
      }
      if (codAux == 1) {
        printf("ERRO: CPF nao encontrado\n");
      }
    }
  } while (opcao != 0);

  codAux = salvar(&lc, strArquivoClientes);
  if (codAux != 0)
    printf("erro ao salvar tarefas em arquivo");
}
