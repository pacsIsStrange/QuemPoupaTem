# QuemPoupaTem
Trabalho Prático — Banco QuemPoupaTem.

 Este projeto foi realizado na matéria de Desenvolvimento de Algorítimos (CC2632), no curso de Ciência da Computação pelo Centro Universitário FEI, semelhante ao que fizemos no semestre passado utilizando python, e nesse semestre é ministrado pelo professor Leonardo Anjoletto Ferreira.

A proposta do trabalho é criar um banco que trabalhe com 2 tipos de conta, a conta Comum que tem os requisitos de cobrar uma taxa de 5% dos débitos realizados, e tem como limite negativo de R$1000, e a conta Plus que cobra uma taxa de 3% dos débitos e permite um saldo negativo de R$5000. O banco deve ser feito somente na linguagem C.

O sistema do banco deve rodar em loop e parar quando o usuário seleciona a opção de sair. Mesmo depois do usuário sair ele consegue retomar por salvarmos suas ações utilizando um arquivo com criptografia binaria. 
Outras opções que temos além da “sair” são: Novo cliente(cadastra um novo cliente utilizando seu CPF, nome, tipo, valor da conta e senha); Apagar cliente(deleta o cliente e seu histórico do banco); Lista de clientes(mostra todos os clientes cadastrados); Débito(pede os dados do cliente e o valor que ele deseja); Depósito(pede os dados do cliente); Extrato(pede os dados do cliente para poder mostrar seu extrato bancário) e Transferência entre contas(pede os dados do cliente e os dados da conta que o dinheiro sera enviado, e cada uma dessas opções foi implementada com uma função diferente.
 No sistema conseguimos armazenar até 1000 clientes e guardamos um histórico de 100 ações feitas pelo usuário.
