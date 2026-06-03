#include <iostream>
using namespace std;

struct no {
    int info;
    struct no * prox;
};
typedef struct no * noPtr;

int inserir(noPtr *, int *);
void retirar(noPtr *, int *);
void listar(noPtr, int);
bool listaVazia(noPtr);

int main(){
    noPtr ult = NULL;
    int op, qtde = 0;
    
    do {
        cin >> op;

        switch(op){
            case 1:
                inserir(&ult, &qtde);

                cout << "\nA lista possui "
                    << qtde
                    << " no(s).\n";

                break;
            case 2: 
                retirar(&ult, &qtde); 
                break;
            case 3: 
                listar(ult, qtde); 
                break;
        }
    } while (op !=0); 
}

void inserir(noPtr *i, int *q){
    noPtr p = new no; // Cria o novo nó na memória

    cout << "\nDigite o valor do elemento: ";
    cin >> p->info;

    if (listaVazia(*i)) {
        *i = p; // Se a lista estava vazia, o 'ult' (*i) aponta para este primeiro nó criado.
        p->prox = *i; // Como só tem ele, o próximo dele aponta para ele mesmo, fechando o círculo.
    } else {
        // Se já tem elementos, *i é o ÚLTIMO nó. Logo, (*i)->prox é o PRIMEIRO nó atual da lista.
        
        p->prox = (*i)->prox; // O novo nó (p) copia o ponteiro do último, passando a apontar para o antigo PRIMEIRO (*i).
        (*i)->prox = p;       // O último nó (*i) deixa de apontar para o antigo primeiro e aponta para o NOVO nó (p).
        
        // NOTA: Como não escrevemos "*i = p;", o ponteiro '*i' NÃO sai do lugar. 
        // Ele continua apontando para o mesmo nó de antes, fazendo com que o novo nó (p) 
        // vire, na prática, o novo PRIMEIRO elemento da nossa lista/pilha.
    }

    *q = *q + 1;
}

void retirar (noPtr *i, int *q) {
    if (!listaVazia(*i)) {
        // PASSO 1: O 'alvo' a ser retirado é o PRIMEIRO nó, ou seja, (*i)->prox
        noPtr p = (*i)->prox; 

        if (*q == 1) {
            // Se só tem 1 elemento, a lista vai ficar vazia
            *i = NULL;
        } else {
            // PASSO 2: O último nó (*i) agora aponta para o SEGUNDO nó da lista
            // (que é o próximo do próximo, ou p->prox)
            (*i)->prox = p->prox; 
        }

        // PASSO 3: Agora sim, deletamos o nó que estava no topo/começo
        delete(p); 
        
        cout << "\nO elemento foi retirado da lista!\n";
        *q = *q - 1;
    } else {
        cout << "\n\nLista Vazia!\n";
    }
}

void listar(noPtr i, int q){
    if (!listaVazia(i)){
        // PASSO CHAVE: i é o último. Para começar do primeiro, 
        // nós movemos o ponteiro para o próximo dele antes de começar a imprimir!
        i = i->prox; 

        cout << "\nElementos da lista: ";
        for (int j = 0; j < q; j++){
            cout << i->info << "\t";
            i = i->prox; // Avança para o próximo nó
        }
        cout << "\n";
    }
    else
        cout << "\n\nLista vazia!\n";
}

bool listaVazia(noPtr i){
    if (i == NULL) {
        return true;  // Está vazia
    } else {
        return false; // Não está vazia
    }
}