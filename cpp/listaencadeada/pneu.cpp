#include <iostream>
using namespace std;

struct pneu{
    int num;
    struct pneu* prox;
};
typdef struct pneu* pneuPtr;
pneuPtr topo = NULL;

bool listaVazia(){
    if(topo == NULL)
        return true;
    else
        return false;
}

void push(){
    pneuPtr p = new pneu;
    int valor;

    cout << "Digite o valor do elemento: ";
    cin >> valor;

    p -> num = valor;
    p -> prox = topo;
    topo = p;
}

void pop(){
    pneuPtr p;
    while(!listaVazia()){
        p = topo;
        topo = topo -> prox;
        delete(p);
        cout<<"\nO elemento foi retirado";
    }
}