#include "lib.h"
#include <stdio.h>
#include <string.h>>

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
  for (int i = 0; i < lc->qtd; i++) {
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

int debito(ListaDeClientes *lc, long long int cpf, float valor) {
  char senha[20];
  printf("Digite a senha do cliente: \n");
  scanf("%s", senha);
  int auxPos;
  int auxBool = 0;
  for (int i = 0; i < lc->qtd; i++) {
    if (lc->clientes[i].cpf == cpf) {
      auxPos = i;
      if (strcmp(senha, lc->clientes[i].senha) == 0){auxBool = 1;}
    }
  }
  if (auxBool == 1) {
    float valorFinal = valor + (valor * retornaTaxa(lc->clientes[auxPos].tipo));
    printf("Valor final debitado: %f\n", valorFinal);
    printf("Saldo antes: %f\n", lc->clientes[auxPos].saldo);
    lc->clientes[auxPos].saldo = lc->clientes[auxPos].saldo - valorFinal;
    printf("Saldo atualizado: %f\n", lc->clientes[auxPos].saldo);
    return 0;
  }

  if (auxBool == 0) {
    return 1;
  } else if (auxBool != 1 && auxBool != 0) {
    printf("auxBool = %d\n", auxBool);
    return 2;
  }
};

int deposito(ListaDeClientes *lc, long long int cpf, float valor) {
  int auxPos;
  int auxBool = 0;
  for (int i = 0; i < lc->qtd; i++) {
    if (lc->clientes[i].cpf == cpf) {
      auxPos = i;
      auxBool = 1;
    }
  }
  if (auxBool == 0) {
    return 1;
  }
  else if (auxBool == 1) {
    printf("Saldo antes: %f\n", lc->clientes[auxPos].saldo);
    lc->clientes[auxPos].saldo = lc->clientes[auxPos].saldo + valor;
    printf("Saldo atualizado: %f\n", lc->clientes[auxPos].saldo);
    return 0;
  }
};

int transferencia(ListaDeClientes *lc, long long int cpfOrigem, long long int cpfDestino, float valor, char *senha){
  int auxPosOrigem = 0;
  int auxPosDestino = 0;
  int auxBoolOrigem = 0;
  int auxBoolDdestino = 0;
  for (int i = 0; i < lc->qtd; i++) {
    printf("i = %d\n", i);
    printf("CPF = %lli\n", lc->clientes[i].cpf);
    printf("Senha = %s\n", senha);
    printf("Senha (i) = %s\n", lc->clientes[i].senha);
    if (lc->clientes[i].cpf == cpfOrigem) {
      printf("AAA\n");
      auxPosOrigem = i;
      if (strcmp(senha, lc->clientes[i].senha) == 0){auxBoolOrigem = 1;}
    }
    else if(lc->clientes[i].cpf == cpfDestino){
      printf("BBB\n");
      auxPosDestino = i;
      auxBoolDdestino = 1;
    }
  }
  if (auxBoolOrigem == 0 && auxBoolDdestino == 0) {
    return 1;
  }
  else if (auxBoolOrigem == 1 && auxBoolDdestino == 0) {
    return 2;
  }
  else if (auxBoolOrigem == 0 && auxBoolDdestino == 1) {
    return 3;
  }
  else if (auxBoolOrigem == 1 && auxBoolDdestino == 1) {
    float valorDebito = valor + valor *(retornaTaxa(lc->clientes[auxPosOrigem].tipo));
    printf("Saldo (origem) antes da transferencia: %f\n", lc->clientes[auxPosOrigem].saldo);
    lc->clientes[auxPosOrigem].saldo = lc->clientes[auxPosOrigem].saldo - valorDebito;
    printf("Saldo (origem) depois da transferência: %f\n-------\n", lc->clientes[auxPosOrigem].saldo);
    printf("Saldo (destino) antes da transferencia: %f\n", lc->clientes[auxPosDestino].saldo);
    lc->clientes[auxPosDestino].saldo = lc->clientes[auxPosDestino].saldo + valor;
    printf("Saldo (destino) depois da transferencia: %f\n", lc->clientes[auxPosDestino].saldo);
    return 0;
  }
  else {return 4;}
};

int carregar(ListaDeClientes *lc, char *strArquivo) {
  FILE *f = fopen(strArquivo, "rb");
  if (f == NULL){
    return 1;
  }
  fread(lc, sizeof(ListaDeClientes), 1, f);
  fclose(f);

  return 0;
}

int salvar(ListaDeClientes *lc, char *strArquivo) {
  FILE *f = fopen(strArquivo, "wb");
  if (f == NULL){
    return 1;
  }
  fwrite(lc, sizeof(ListaDeClientes), 1, f);
  fclose(f);

  return 0;
}

void copiaString(char string1[], char string2[]) {
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

int tamanho(char string[]) {
  int aux = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    aux += 1;
  }
  return aux;
}

float retornaTaxa(int tipo) {
  if (tipo == 1) {
    return 0.05;
  } else if (tipo == 2) {
    return 0.03;
  } else {
    printf("Erro desconhecido ao calcular taxa. Verificar tipo da conta do "
           "cliente.");
  }
}
