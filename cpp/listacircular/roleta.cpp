#include <iostream>
#include <cstdlib> 
#include <ctime>  
#include <iomanip> 

using namespace std;

struct no{
    int info;
    struct no * prox;
};
typedef struct no *noPtr;

void inicializarRoleta(noPtr *ult, int *qtd);
void listarRoleta(noPtr ult, int qtd);
void girarRoleta(noPtr ult, int aposta, float *carteira, float valorAposta);

int main(){
    srand(time(NULL));

    noPtr ult = NULL;
    int op, qtd = 0;
    float carteira = 100.0;
    float valorAposta;

    inicializarRoleta(&ult, &qtd);

    cout << "=====================================\n"
         << "Bem vindo à Roleta da Meia Noite\n"
         << "=====================================\n"
         << "\nA roleta possui " << qtd << " numeros.\n";

    cout << "Opções: \n"
         << "\n1 - Vizualizar números da roleta\n"
         << "\n2 - Apostar um número na roleta\n"
         << "\n0 - Sair\n"
         << "\nDigite uma opção: ";
    cin >> op;

    while(op != 0){
        switch (op){
            case 1:
                listarRoleta(ult, qtd);
                break;

            case 2:
                int aposta;
                cout << "\nSeu saldo atual: R$" << fixed << setprecision(2) << carteira
                     << "\n==== Ganho = valor apostado x 35 ===="
                     << "\nQuanto você deseja apostar? ";
                cin  >> valorAposta;

                if(valorAposta >= 0 && valorAposta <= carteira){
                   
                    cout << "\nDigite o numero da sua aposta (0 a 36): ";
                    cin >> aposta;

                    if(aposta < 0 || aposta > 36){
                        cout << "Numero invalido. Tente novamente.\n";
                    } else {
                        girarRoleta(ult, aposta, &carteira, valorAposta);
                    }
                } else {
                    cout << "Saldo insuficiente ou valor inválido! Tente novamente!\n";
                }

                break;
                
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

        if(carteira <= 0){
            cout << "\nVOCÊ FALIU! Seu saldo acabou!\n";
            op = 0;
        } else {
            char novaAposta;
            cout << "\nDeseja continuar no jogo? (S-SIM / N-NAO): ";
            cin >> novaAposta;

            if(novaAposta == 'S' || novaAposta == 's'){ 
                cout << "\nEscolha uma opcao: \n"
                    << "1 - Visualizar numeros da roleta\n"
                    << "2 - Apostar um numero na roleta\n"
                    << "0 - Sair\n"
                    << "Sua opcao: ";
                cin >> op; 
            }
            else if(novaAposta == 'N' || novaAposta == 'n'){
                cout << "\nEncerrando o jogo. Obrigado por jogar!";
                op = 0;
            }
            else {
                cout << "\nEntrada invalida! Encerrando o jogo por seguranca.\n";
                op = 0;
            }
        }
    }

    cout << "\nVocê saiu do cassino com: R$" << fixed << setprecision(2) << carteira << "\n";
    return 0;
}

void inicializarRoleta(noPtr *ult, int *qtd){
    for( int i = 0; i <= 36; i++){
        noPtr p = new no;
        p->info = i;

        if(*ult == NULL){
            *ult = p;
            (*ult)->prox = p;
        }else{
            p->prox = (*ult)->prox;
            (*ult)->prox = p;
            *ult = p;
        }

        *qtd += 1;
    }
}

void listarRoleta(noPtr ult, int qtd){
    if(ult != NULL){
        noPtr atual = ult->prox; 
        
        cout << "\nNumeros na roleta: ";
        for (int i = 0; i < qtd; i++){
            cout << atual->info << " ";
            atual = atual->prox;
        }
        cout << "\n";
    }
}

void girarRoleta(noPtr ult, int aposta, float *carteira, float valorAposta){
    noPtr bolinha = ult->prox;

    int impulso = (rand() %50) + 45;

    cout << "\n* A roleta esta girando...";

    for(int i = 0; i < impulso; i++){
        bolinha = bolinha->prox;
    }

    cout << "\n=======================================";
    cout << "\n>>>  A BOLINHA PAROU NO NUMERO: " << bolinha->info << "  <<<";
    cout << "\n=======================================\n";

    if (bolinha->info == aposta) {
        *carteira += (valorAposta * 35);
        cout << "PARABENS! Voce acertou o numero e ganhou R$" << fixed << setprecision(2) << (valorAposta * 35) << "!\n"
             << "Saldo: R$ " << *carteira;
    } else {
        *carteira -= valorAposta;
        cout << "Nao foi dessa vez! Voce perdeu R$" << fixed << setprecision(2) << valorAposta << ".\n"
             << "Saldo: R$ " << *carteira;
    }
}