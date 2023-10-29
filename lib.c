#include "lib.h"
#include <stdio.h>
#include <string.h>

int novoCliente(ListaDeClientes *lc) {
  if (lc->qtd >= TOTAL_CLIENTES) // VERIFICA SE O NÚMERO DE CLIENTES NA LISTA ULTRAPASSA O LIMITE ESTABELECIDO DE 1000
    return 1;
  
  Cliente *c = &lc->clientes[lc->qtd]; // GUARDA A STRUCT DO TIPO 'Cliente' PRESENTE NA POSIÇÃO '[lc->qtd]' (OU SEJA, NA PRIMEIRA POSIÇÃO APÓS O ÚLTIMO CLIENTE CADASTRADO) NA VARIAVEL 'c'
// ATRIBUI OS INPUTS DO USUÁRIO NOS DEVIDOS ELEMENTOS DA STRUCT 'c'
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

  c->ext.qtd = 0; // DEFINE A QUANTIDADE DE OPERAÇÕES ON EXTRATO DO CLIENTE COMO 0
  
  lc->qtd++; // AUMENTA A QUANTIDADE DE CLIENTES REGISTRADOS NA LISTA
  
  return 0;
}

int apagaCliente(ListaDeClientes *lc) {
  if (lc->qtd == 0) { // VERIFICA SE O NÚMERO DE CLIENTES É IGUAL A ZER0 (OU SEJA, SE NÃO HÁ CLIENTES CADASTRADOS NA LISTA)
    return 1;
  }
  int auxBool = 0; // VARIÁVEL BOOLEANA REFERENTE AO ENCONTRO OU NÃO DO CPF DIGITADO PELO USUÁRIO NA LISTA
  int auxPos = (lc->qtd + 1);
  long long int cpf;
  printf("Digite o cpf do cliente que deseja deletar: \n");
  scanf("%lli", &cpf);
  for (int i = 0; i < lc->qtd; i++) {
    if (lc->clientes[i].cpf == cpf) {
      auxPos = i;
    }
  }
// ITERAÇÃO PARA GUARDAR AS INFORMAÇÕES DO CLIENTE NA POSIÇÃO SEGUINTE AOS CLIENTES DA LISTA NA STRUCT DA POSIÇÃO DO PRÓRPIO CLIENTE, A PARTIR DA POSIÇÃO EM QUE O CPF DIGITADO PELO USUÁRIO FOI ENCONTRADO
  for (; auxPos < lc->qtd - 1; auxPos++) {
    strcpy(lc->clientes[auxPos].nome, lc->clientes[auxPos + 1].nome);
    lc->clientes[auxPos].cpf = lc->clientes[auxPos + 1].cpf;
    lc->clientes[auxPos].tipo = lc->clientes[auxPos + 1].tipo;
    lc->clientes[auxPos].saldo = lc->clientes[auxPos + 1].saldo;
    strcpy(lc->clientes[auxPos].senha, lc->clientes[auxPos + 1].senha);
  }

  lc->qtd--; // DIMINUI O NÚMERO DE CLIENTES NA LISTA, PARA QUE CASO SEJA REGISTRADO UM NOVO CLIENTE NÃO HAJA UM ESPAÇO VAZIO NA LISTA DE CLIENTES

  return 0;
}

int listarClientes(ListaDeClientes *lc) {
  if (lc->qtd == 0){
    return 1;
  }
  // ITERAÇÃO PARA EXIBIR AS INFORMAÇÕES DAS STRUCTS DO TIPO 'Cliente' PRESENTES NA LSTA
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
  int auxBool = 0; // VARIÁVEL BOOLEANA REFERENTE AO ENCONTRO E VALIDAÇÃO DO CPF E SENHA DIGITADOS PELO USUÁRIO
  for (int i = 0; i < lc->qtd; i++) {
    if (lc->clientes[i].cpf == cpf) {
      auxPos = i;
      if (strcmp(senha, lc->clientes[i].senha) == 0){auxBool = 1;}
    }
  }
  float valorFinal = valor + (valor * retornaTaxa(lc->clientes[auxPos].tipo)); // ADICIONA A TAXA AO VALOR DO DÉBITO
  if (auxBool == 1 && retornaBoolLimite(lc, valorFinal, auxPos)) { // CHAMA A FUNÇÃO 'retornaBoolLimite' PARA VERIFICAR SE O SALDO DO CLIENTE ATENDE OS LIMITES DE SALDO ESTABELECIDOS PARA O TIPO DE CONTA DELE
    double valorFinal = valor + (valor * retornaTaxa(lc->clientes[auxPos].tipo));
    printf("Valor final debitado: %f\n", valorFinal);
    printf("Saldo antes: %f\n", lc->clientes[auxPos].saldo);
    lc->clientes[auxPos].saldo = lc->clientes[auxPos].saldo - valorFinal;
    printf("Saldo atualizado: %f\n", lc->clientes[auxPos].saldo);
    char desc[20] = "Debito";
    strcpy(lc->clientes[auxPos].ext.operacoes[lc->clientes[auxPos].ext.qtd].descricao, desc);
    lc->clientes[auxPos].ext.operacoes[lc->clientes[auxPos].ext.qtd].valor = valorFinal;
    lc->clientes[auxPos].ext.operacoes[lc->clientes[auxPos].ext.qtd].taxa = retornaTaxa(lc->clientes[auxPos].tipo);
    
    lc->clientes[auxPos].ext.qtd++;

    return 0;
    } else if(auxBool == 0) {
    return 1;
  } else if (auxBool != 1 && auxBool != 0) {
    printf("auxBool = %d\n", auxBool);
    return 2;
  } else if (retornaBoolLimite(lc, valorFinal, auxPos) == 0) {printf("saldo insuficiente para realizar a operacao\n");}
}

int deposito(ListaDeClientes *lc, long long int cpf, float valor) {
  int auxPos;
  int auxBool = 0; // VARIÁVEL BOOLEANA REFERENTE AO ENCONTRO E VALIDAÇÃO DO CPF DIGITADO PELO USUÁRIO
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
    char desc[20] = "Deposito";
    strcpy(lc->clientes[auxPos].ext.operacoes[lc->clientes[auxPos].ext.qtd].descricao, desc);
    lc->clientes[auxPos].ext.operacoes[lc->clientes[auxPos].ext.qtd].valor = valor;
    lc->clientes[auxPos].ext.operacoes[lc->clientes[auxPos].ext.qtd].taxa = 0;

    lc->clientes[auxPos].ext.qtd++;
    return 0;
  }
}

int escreveExtrato(ListaDeClientes *lc, long long int cpf){
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
  if (auxBool == 1){
    FILE *f = fopen("extrato.txt", "w"); // ABRE O ARQUIVO 'extrato.txt' NO MODO DE ESCRITA
    fprintf(f, "--- EXTRATO DO CLIENTE %s ---\nCPF = %lld\n", lc->clientes[auxPos].nome, lc->clientes[auxPos].cpf);
    for(int i = 0; i < lc->clientes[i].ext.qtd; i++){
      fprintf(f, "Operacao = %s    Valor = %f    Taxa = %f\n", lc->clientes[auxPos].ext.operacoes[i].descricao, lc->clientes[auxPos].ext.operacoes[i].valor, lc->clientes[auxPos].ext.operacoes[i].taxa);
    }
    fclose(f); // FECHA O ARQUIVO PARA SALVAR AS MUDANÇAS
  return 0;
  }
}

int transferencia(ListaDeClientes *lc, long long int cpfOrigem, long long int cpfDestino, float valor, char *senha){ // ESSENCIALMENTE UMA MISTURA DAS FUNÇÕES DE DÉBITO E DEPÓSITO
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
      auxPosOrigem = i;
      if (strcmp(senha, lc->clientes[i].senha) == 0){auxBoolOrigem = 1;}
    }
    else if(lc->clientes[i].cpf == cpfDestino){
      auxPosDestino = i;
      auxBoolDdestino = 1;
    }
  }
  float valorDebito = valor + valor *(retornaTaxa(lc->clientes[auxPosOrigem].tipo));
  if (auxBoolOrigem == 0 && auxBoolDdestino == 0) {
    return 1;
  }
  else if (auxBoolOrigem == 1 && auxBoolDdestino == 0) {
    return 2;
  }
  else if (auxBoolOrigem == 0 && auxBoolDdestino == 1) {
    return 3;
  }
  else if (auxBoolOrigem == 1 && auxBoolDdestino == 1 && retornaBoolLimite(lc, valorDebito, auxPosOrigem)) {
    printf("Saldo (origem) antes da transferencia: %f\n", lc->clientes[auxPosOrigem].saldo);
    lc->clientes[auxPosOrigem].saldo = lc->clientes[auxPosOrigem].saldo - valorDebito;
    printf("Saldo (origem) depois da transferência: %f\n-------\n", lc->clientes[auxPosOrigem].saldo);
    printf("Saldo (destino) antes da transferencia: %f\n", lc->clientes[auxPosDestino].saldo);
    lc->clientes[auxPosDestino].saldo = lc->clientes[auxPosDestino].saldo + valor;
    printf("Saldo (destino) depois da transferencia: %f\n", lc->clientes[auxPosDestino].saldo);
    // ESCREVE AS INFORMAÇÕES DA OPERAÇÃO NOS EXTRATOS DE AMBOS OS CLIENTES ENVOLVIDOS
    char desc1[20] = "Transferencia-origem";
    strcpy(lc->clientes[auxPosOrigem].ext.operacoes[lc->clientes[auxPosOrigem].ext.qtd].descricao, desc1);
    lc->clientes[auxPosOrigem].ext.operacoes[lc->clientes[auxPosOrigem].ext.qtd].valor = valorDebito;
    lc->clientes[auxPosOrigem].ext.operacoes[lc->clientes[auxPosOrigem].ext.qtd].taxa = retornaTaxa(lc->clientes[auxPosOrigem].tipo);

    lc->clientes[auxPosOrigem].ext.qtd++;

    char desc2[20] = "Transferencia-dest";
    strcpy(lc->clientes[auxPosDestino].ext.operacoes[lc->clientes[auxPosDestino].ext.qtd].descricao, desc2);
    lc->clientes[auxPosDestino].ext.operacoes[lc->clientes[auxPosDestino].ext.qtd].valor = valorDebito;
    lc->clientes[auxPosDestino].ext.operacoes[lc->clientes[auxPosDestino].ext.qtd].taxa = 0;

    lc->clientes[auxPosDestino].ext.qtd++;
    
    return 0;
  } else if (retornaBoolLimite(lc, valorDebito, auxPosOrigem)){
    printf("saldo insuficiente na conta de origem para realizar a operacao.\n");
  } else {return 4;}
}

int carregarClientes(ListaDeClientes *lc, char *strArquivo) {
  FILE *f = fopen(strArquivo, "rb"); // ABRE O ARQUIVO NO MODO DE LEITURA BINÁRIA
  if (f == NULL){
    return 1;
  }
  fread(lc, sizeof(ListaDeClientes), 1, f); // LÊ A SCTRUCT PRESENTE NO ARQUIVO BRINÁRIO E ARMAZENA NA VARIÁVEL 'lc' 
  fclose(f);

  return 0;
}

int salvarClientes(ListaDeClientes *lc, char *strArquivo) {
  FILE *f = fopen(strArquivo, "wb"); // ABRE O ARQUIVO NO MODO DE ESCRITA BINÁRIA
  if (f == NULL){
    return 1;
  }
  fwrite(lc, sizeof(ListaDeClientes), 1, f); // SOBRESCREVE O CONTEÚDO DO ARQUIVO COM A STRUCT DA VARIÁVEL 'lc'
  fclose(f);

  return 0;
}

int retornaBoolLimite(ListaDeClientes *lc, float valor, int auxPos){ // VERIFICA SE A CONTA DO CLIENTE ATENDE OS REQUISITOS MÍNIMOS DE SALDO PARA REALIZAR UMA OPERAÇÃO A PARTIR DOS LIMITES ESTABELECIDOS PARA CADA TIPO DA CONTA DO CLIENTE
  float limite = 0;
  if (lc->clientes[auxPos].tipo == 1){
    limite = (-1000.00);
  } else if (lc->clientes[auxPos].tipo == 2){
    limite = (-5000.00);
  } else {printf("erro desconhecido, verificar tipo da conta do cliente.\n");}
  if (lc->clientes[auxPos].saldo - valor >= limite){return 1;}
  else {return 0;}
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

float retornaTaxa(int tipo) { // RETORNA O VALOR DA TAXA QUE SERÁ APLICADA À OPERAÇÃO DE ACORDO COM O TIPO DA CONTA DO CLIENTE
  if (tipo == 1) {
    return 0.05;
  } else if (tipo == 2) {
    return 0.03;
  } else {
    printf("Erro desconhecido ao calcular taxa. Verificar tipo da conta do "
           "cliente.");
  }
}
