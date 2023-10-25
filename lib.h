#define TOTAL_CLIENTES 1000

typedef struct {
  char descricao[20];
  float valor;
  float taxa;
} Operacao;

typedef struct {
  Operacao operacoes[100];
  int qtd;
} Extrato;

typedef struct {
  char nome[50];
  long long int cpf;
  int tipo;
  float saldo;
  char senha[20];
  Extrato ext;
} Cliente;

typedef struct {
  Cliente clientes[1000];
  int qtd;
} ListaDeClientes;

int novoCliente(ListaDeClientes *lc);
int apagaCliente(ListaDeClientes *lc);
int listarClientes(ListaDeClientes *lc);
int debito(ListaDeClientes *lc, long long int cpf, float valor);
int deposito(ListaDeClientes *lc, long long int cpf, float valor);
int escreveExtrato(ListaDeClientes *lc, long long int cpf);
int transferencia(ListaDeClientes *lc, long long int cpfOrigem, long long int cpfDestino, float valor, char *senha);
int carregarClientes(ListaDeClientes *lc, char *strArquivo);
int salvarClientes(ListaDeClientes *lc, char *strArquivo);
void copiaString(char string1[], char string2[]);
int tamanho(char string[]);
float retornaTaxa(int tipo);
int retornaBoolLimite(ListaDeClientes *lc, float valor, int auxPos);

void exibeMenu();
