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

int novoCliente(ListaDeClientes *lc);
int apagaCliente(ListaDeClientes *lc);
int listarClientes(ListaDeClientes *lc);
int debito(ListaDeClientes *lc, long long int cpf, float valor);
int deposito(ListaDeClientes *lc, long long int cpf, float valor);
int transferencia(ListaDeClientes *lc, long long int cpfOrigem, long long int cpfDestino, float valor, char *senha);
int carregar(ListaDeClientes *lc, char *strArquivo);
int salvar(ListaDeClientes *lc, char *strArquivo);
void copiaString(char string1[], char string2[]);
int tamanho(char string[]);
float retornaTaxa(int tipo);

void exibeMenu();
