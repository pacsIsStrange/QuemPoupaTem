#define TOTAL_CLIENTES 1000

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

typedef struct {
  char descricao[20];
  int valor;
  double taxa;
  long long int cpf;
} Operacao;

typedef struct {
  Operacao operacoes[100000];
  int qtd;
} Extrato;

typedef struct {

} operacao;

int novoCliente(ListaDeClientes *lc);
int apagaCliente(ListaDeClientes *lc);
int listarClientes(ListaDeClientes *lc);
int debito(ListaDeClientes *lc, long long int cpf, char *senha, float valor);
int deposito(ListaDeClientes *lc, long long int cpf, float valor);
int transferencia(ListaDeClientes *lc, long long int cpfOrigem,
                  const char *senha, long long int cpfDestino, float valor);
int carregar(ListaDeClientes *lc, char *strArquivo);
int salvar(ListaDeClientes *lc, char *strArquivo);
void copiaString(char string1[], char string2[]);
int tamanho(char string[]);
float retornaTaxa(int tipo);
int carregarExtrato(Extrato *ext, char *strArquivo);
int salvarExtrato(Extrato *ext, char *strArquivo);
int buscarExtrato(Extrato *ext, long long int cpf, char *senha);
int registrarExtrato(Extrato *ext, char descricao[20], int valor,
double taxa, long long int cpf, char *strArquivo);

void exibeMenu();
