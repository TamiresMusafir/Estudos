#include <iostream>
using namespace std;

struct no {
    int info;
    struct no * ant;
    struct no * prox;
};
typedef struct no * noPtr;

void inserir(noPtr *);
void retirar(noPtr *);
void listar(noPtr);
bool listaVazia(noPtr);

main(){
    noPtr topo = NULL;
    int op;
    
    do {
        cin >> op;
        switch(op){
            case 1: inserir(&topo); 
                break;
            case 2: retirar(&topo); 
                break;
            case 3: listar(topo); 
                break;
        }
    } while (op !=0); 
}

void inserir (noPtr * i) {
    noPtr p = new no;

    cout << "\nDigite o valor do elemento: ";
    cin >> p->info;

    p->ant = NULL;

    if (listaVazia(*i))
        p->prox = NULL;
    else {
        p->prox = *i;
        (*i)->ant = p;
    }
    *i = p;
}

void retirar (noPtr * i) {
    noPtr p = *i;

    if (!listaVazia(*i)){
        if (p->prox == NULL)
            *i = NULL;
        else{
            *i = p->prox; // *i = *i->prox;
            (*i)->ant = NULL; //p->prox->ant = NULL;
        }
        delete(p);
        cout << "\nO elemento foi retirado da lista!\n";
    }
    else 
        cout << "\n\nLista está Vazia!\n";
}

void listar(noPtr p) {
    if (!listaVazia(p)){
        cout << "\nElementos da lista : \n";
        cout << "INICIO";
        while (p != NULL){
            cout << " --> " << p->info;
            p = p->prox;
        }
        cout << " -- > NULL";
    }
    else
        cout << "\n\nLista está Vazia!\n";
}

bool listaVazia(noPtr i){
    if (i == NULL) {
        return true;  
    } else {
        return false;
    }
}