#include "lib.h"
#include <stdio.h>

int novoCliente(ListaDeClientes *lc) {
  if (lc->qtd >= TOTAL_CLIENTES)
    return 1;

  Cliente *c = &lc->clientes[lc->qtd];

  printf("Digite o nome do cliente: \n");
  scanf("%s", c->nome);

  printf("Digite o CPF do cliente: \n");
  scanf("%lld", &c->cpf);

  printf("Digite o tipo da conta do cliente: \n");
  scanf("%d", &c->tipo);

  printf("Digite o valor inicial da conta do cliente: \n");
  scanf("%f", &c->saldo);

  printf("Digite a senha do cliente: \n");
  scanf("%s", c->senha);

  lc->qtd++;

  return 0;
}

int apagaCliente(ListaDeClientes *lc) {
  if (lc->qtd == 0) {
    return 1;
  }
  int auxBool = 0;
  int auxPos = (lc->qtd + 1);
  long long int cpf;
  printf("Digite o cpf do cliente que deseja deletar: \n");
  scanf("%lli", &cpf);
  // printf("cpf base = %lli\n", cpf);
  for (int i = 0; i < lc->qtd; i++) {
    // printf("for i = %d\n", i);
    // printf("cpf = %lli\n", lc->clientes[i].cpf);
    // printf("cpf base = %lli\n", cpf);
    if (lc->clientes[i].cpf == cpf) {
      auxPos = i;
      printf("Cpf encontrado na posicao %d (auxpos = %d)\n", i, auxPos);
    }
  }

  for (; auxPos < lc->qtd - 1; auxPos++) {
    copiaString(lc->clientes[auxPos].nome, lc->clientes[auxPos + 1].nome);
    lc->clientes[auxPos].cpf = lc->clientes[auxPos + 1].cpf;
    lc->clientes[auxPos].tipo = lc->clientes[auxPos + 1].tipo;
    lc->clientes[auxPos].saldo = lc->clientes[auxPos + 1].saldo;
    copiaString(lc->clientes[auxPos].senha, lc->clientes[auxPos + 1].senha);
  }

  lc->qtd--;

  return 0;
}
int listarClientes(ListaDeClientes *lc) {
  if (lc->qtd == 0)
    return 1;

  for (int i = 0; i < lc->qtd; i++) {
    printf("--- CLIENTE NUMERO %d ---\nNome: %s\nCPF: %lld\nSaldo: %f\n", i + 1,
           lc->clientes[i].nome, lc->clientes[i].cpf, lc->clientes[i].saldo);
    if (lc->clientes[i].tipo == 1) {
      printf("Tipo: Comum\n");
    } else if (lc->clientes[i].tipo == 2) {
      printf("Tipo: Plus\n");
    } else {
      printf("Tipo invalido\n");
    }
  }

  return 0;
}

int debito(ListaDeClientes *lc, long long int cpf, char *senha, float valor) {
  int auxPos;
  int auxBool;
  printf("AAA");
  for (int i = 0; i < lc->qtd; i++) {
    printf("%lld", lc[i].clientes->cpf);
    printf("%s", lc[i].clientes->senha);
    if (lc[i].clientes->cpf == cpf && lc[i].clientes->senha == senha) {
      printf("AAA");
      auxPos = i;
      auxBool = 1;
    }
  }
  printf("Posicao do cliente = %d", auxPos);
  if (auxBool == 0) {
    return 1;
  } else if (auxBool != 1 && auxBool != 0) {
    return 2;
  }
  int saldo = lc[auxPos].clientes->saldo;
  lc[auxPos].clientes->saldo = saldo - valor;
  return 0;
};

int deposito(ListaDeClientes *lc, long long int cpf, float valor);

int transferencia(ListaDeClientes *lc, long long int cpfOrigem,
                  const char *senha, long long int cpfDestino, float valor);

int carregar(ListaDeClientes *lc, char *strArquivo) {
  FILE *f = fopen(strArquivo, "rb");
  if (f == NULL)
    return 1;

  fread(lc, sizeof(ListaDeClientes), 1, f);
  fclose(f);

  return 0;
}

int salvar(ListaDeClientes *lc, char *strArquivo) {
  FILE *f = fopen(strArquivo, "wb");
  if (f == NULL)
    return 1;

  fwrite(lc, sizeof(ListaDeClientes), 1, f);
  fclose(f);

  return 0;
}

int copiaString(char string1[], char string2[]) {
  int t1 = tamanho(string1);
  int len = t1;
  int t2 = tamanho(string2);
  if (t2 < t1) {
    printf("Erro: string receptora menor do que o necessário");
  } else {
    for (int i = 0; i < len; i++) {
      string2[i] = string1[i];
    }
  }
}

void exibeMenu() {
  printf("--- MENU ---\n");
  printf("1. Cadastrar cliente\n");
  printf("2. Deletar cliente\n");
  printf("3. Listar clientes\n");
  printf("4. Debito\n");
  printf("5. Deposito\n");
  printf("6. Extrato\n");
  printf("7. Transferencia entre contas\n");
  printf("0. Sair\n");
}
