#define TOTAL_CLIENTES 1000

typedef struct {
  char descricao[20];
  double valor;
  double taxa;
  long long int cpf;
} Operacao;

typedef struct {
  Operacao operacoes[100000];
  int qtd;
} Extrato;

typedef struct {
  char nome[100];
  long long int cpf;
  int tipo;
  float saldo;
  char senha[20];
} Cliente;

typedef struct {
  Cliente clientes[TOTAL_CLIENTES];
  int qtd;
} ListaDeClientes;

int novoCliente(ListaDeClientes *lc);
int apagaCliente(ListaDeClientes *lc);
int listarClientes(ListaDeClientes *lc);
int debito(Extrato *ext, ListaDeClientes *lc, long long int cpf, float valor);
int deposito(Extrato *ext, ListaDeClientes *lc, long long int cpf, float valor);
int escreveExtrato(Extrato ext, ListaDeClientes *lc, long long int cpf, char *senha);
int transferencia(Extrato *ext, ListaDeClientes *lc, long long int cpfOrigem, long long int cpfDestino, float valor, char *senha);
int carregarClientes(ListaDeClientes *lc, char *strArquivo);
int salvarClientes(ListaDeClientes *lc, char *strArquivo);
int carregarExtrato(Extrato *ext, char *strArquivo);
int salvarExtrato(Extrato *ext, char *strArquivo);
void copiaString(char string1[], char string2[]);
int tamanho(char string[]);
float retornaTaxa(int tipo);

void exibeMenu();
