/*
===========================================================================
Centro Universitario de Vicosa - UNIVICOSA
 Nome :Vinicius dos Passos Ribeiro
Matricula : 28770
Disciplina: INF101 - Programacao de Computadores I
Trabalho - Sistema de Registro e Gestao de Contas Bancarias (ETAPA 2)
===========================================================================
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_CONTAS = 100;
const int MAX_MOVIMENTACOES = 500;

int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int quantidadeContas = 0;

int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

// variaveis usadas no menu
int opcao, numero, indice;
double valor;
int numeroOrigem, numeroDestino, indiceOrigem, indiceDestino;
bool achou;

int main() {
    cout << fixed << setprecision(2);

    // Menu
    do {
        cout << endl;
        cout << "MENU" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas cadastradas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Depositar" << endl;
        cout << "5 - Sacar" << endl;
        cout << "6 - Transferir" << endl;
        cout << "7 - Extrato" << endl;
        cout << "8 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // se digitou letra em vez de numero
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida, digite apenas numeros: ";
            cin >> opcao;
        }

        switch (opcao) {
            case 1:
                // cadastrar conta
                if (quantidadeContas < MAX_CONTAS) {
                    cout << "Numero da conta: ";
                    cin >> numero;
                    
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Entrada invalida, digite apenas numeros: ";
                        cin >> numero;
                    }

                    // verifica se o numero ja existe
                    achou = false;
                    for (int i = 0; i < quantidadeContas; i++) {
                        if (numeroConta[i] == numero) {
                            achou = true;
                        }
                    }

                    if (achou) {
                        cout << "Ja existe uma conta com esse numero." << endl;
                    } else {
                        numeroConta[quantidadeContas] = numero;

                        cin.ignore(1000, '\n');
                        cout << "Nome do Cliente: ";
                        getline(cin, nomeCliente[quantidadeContas]);
                        
                        cout << "CPF: ";
                        cin >> cpf[quantidadeContas];

                        // repete ate digitar 1 ou 2
                        do {
                            cout << "Tipo da conta (1 - Corrente, 2 - Poupanca): ";
                            cin >> tipoConta[quantidadeContas];
                            
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                tipoConta[quantidadeContas] = 0;
                            }
                        } while (tipoConta[quantidadeContas] != 1 && tipoConta[quantidadeContas] != 2);

                        saldo[quantidadeContas] = 0;
                        contaAtiva[quantidadeContas] = true;
                        quantidadeContas++;
                        
                        cout << "Conta cadastrada com sucesso!" << endl;
                    }
                } else {
                    cout << "Limite maximo de contas atingido!" << endl;
                }
                break;

            case 2:
                // listar contas
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada." << endl;
                } else {
                    for (int i = 0; i < quantidadeContas; i++) {
                        cout << "-----------------------------------" << endl;
                        cout << "CONTA " << i + 1 << ":" << endl;
                        cout << "Numero da Conta: " << numeroConta[i] << endl;
                        cout << "Cliente: " << nomeCliente[i] << endl;
                        cout << "CPF: " << cpf[i] << endl;
                        
                        if (tipoConta[i] == 1) {
                            cout << "Tipo: Corrente" << endl;
                        } else {
                            cout << "Tipo: Poupanca" << endl;
                        }
                        
                        cout << "Saldo: R$ " << saldo[i] << endl;
                    }
                    cout << "-----------------------------------" << endl;
                }
                break;

            case 3:
                // consultar conta
                cout << "Numero da conta: ";
                cin >> numero;

                // procura a conta pelo numero
                indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else {
                    cout << "-----------------------------------" << endl;
                    cout << "Numero da Conta: " << numeroConta[indice] << endl;
                    cout << "Cliente: " << nomeCliente[indice] << endl;
                    cout << "CPF: " << cpf[indice] << endl;
                    
                    if (tipoConta[indice] == 1) {
                        cout << "Tipo: Corrente" << endl;
                    } else {
                        cout << "Tipo: Poupanca" << endl;
                    }
                    
                    cout << "Saldo: R$ " << saldo[indice] << endl;
                    cout << "-----------------------------------" << endl;
                }
                break;

            case 4:
                // depositar
                cout << "Numero da conta: ";
                cin >> numero;

                // procura a conta pelo numero
                indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "Conta inativa." << endl;
                } else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "Historico cheio." << endl;
                } else {
                    cout << "Valor do deposito: ";
                    cin >> valor;

                    if (valor <= 0) {
                        cout << "O valor precisa ser maior que zero." << endl;
                    } else {
                        saldo[indice] = saldo[indice] + valor;

                        // registra a movimentacao
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Deposito realizado. Saldo: R$ " << saldo[indice] << endl;
                    }
                }
                break;

            case 5:
                // sacar
                cout << "Numero da conta: ";
                cin >> numero;

                // procura a conta pelo numero
                indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "Conta inativa." << endl;
                } else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "Historico cheio." << endl;
                } else {
                    cout << "Valor do saque: ";
                    cin >> valor;

                    if (valor <= 0) {
                        cout << "O valor precisa ser maior que zero." << endl;
                    } else if (valor > saldo[indice]) {
                        cout << "Saldo insuficiente." << endl;
                    } else {
                        saldo[indice] = saldo[indice] - valor;

                        // registra a movimentacao
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Saque realizado. Saldo: R$ " << saldo[indice] << endl;
                    }
                }
                break;

            case 6:
                // transferir
                cout << "Conta de origem: ";
                cin >> numeroOrigem;
                cout << "Conta de destino: ";
                cin >> numeroDestino;

                // procura as duas contas
                indiceOrigem = -1;
                indiceDestino = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroOrigem) {
                        indiceOrigem = i;
                    }
                    if (numeroConta[i] == numeroDestino) {
                        indiceDestino = i;
                    }
                }

                if (indiceOrigem == -1 || indiceDestino == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else if (indiceOrigem == indiceDestino) {
                    cout << "As contas precisam ser diferentes." << endl;
                } else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                    cout << "Conta inativa." << endl;
                } else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                    // precisa de espaco para 2 registros
                    cout << "Historico sem espaco." << endl;
                } else {
                    cout << "Valor da transferencia: ";
                    cin >> valor;

                    if (valor <= 0) {
                        cout << "O valor precisa ser maior que zero." << endl;
                    } else if (valor > saldo[indiceOrigem]) {
                        cout << "Saldo insuficiente." << endl;
                    } else {
                        saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
                        saldo[indiceDestino] = saldo[indiceDestino] + valor;

                        // saida da origem
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        // entrada no destino
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Transferencia realizada." << endl;
                    }
                }
                break;

            case 7:
                // extrato
                cout << "Numero da conta: ";
                cin >> numero;

                // procura a conta pelo numero
                indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else {
                    cout << "-----------------------------------" << endl;
                    cout << "Extrato da conta " << numero << " - " << nomeCliente[indice] << endl;

                    // mostra so as movimentacoes dessa conta
                    achou = false;
                    for (int i = 0; i < quantidadeMovimentacoes; i++) {
                        if (contaMovimentacao[i] == numero) {
                            achou = true;
                            if (tipoMovimentacao[i] == 'D') {
                                cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                            } else if (tipoMovimentacao[i] == 'S') {
                                cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                            }
                        }
                    }

                    if (!achou) {
                        cout << "Nenhuma movimentacao." << endl;
                    }
                    
                    cout << "Saldo atual: R$ " << saldo[indice] << endl;
                    cout << "-----------------------------------" << endl;
                }
                break;

            case 8:
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "Opcao invalida, digite novamente." << endl;
        }
    } while (opcao != 8);

    return 0;
}