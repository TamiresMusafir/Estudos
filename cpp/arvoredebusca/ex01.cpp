#include <iostream>
using namespace std;

struct no{
    int info;
    struct no *esq, *dir;
};
typedef struct no *noPtr;

void inserir(noPtr *p, int x);
void remover(noPtr *p, int x);
noPtr buscar(noPtr p, int x);
noPtr maior(noPtr *p);
bool enderecoVazio(noPtr p);
void listarEmOrdem(noPtr p);
void listarPreOrdem(noPtr p);
void listarPosOrdem(noPtr p);
int menu();
int listarNos();

int main(){

}

void inserir(noPtr *p, int x){
    if(enderecoVazio(*p)){
        *p = new no;
        (*p)->info = x;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
    }else{
        if(x<(*p)->info)
            inserir(&(*p)->esq, x);
        else
            inserir(&(*p)->dir, x);
    }       
}

void remover(noPtr *p, int x){
    noPtr aux;
    if(!enderecoVazio(*p)){
        aux = *p;
        if((*p)->esq==NULL)
            *p = (*p)->dir;
        else
            if((*p)->dir==NULL)
                *p = (*p)->esq;
            else{
                aux = maior(&(*p)->esq);
                (*p)->info = aux->info;
            }
        delete(aux);
        cout << "\nO elemento foi removido.";
    }else{
        if(x>(*p)->info)
            remover(&(*p)->esq, x);
        else    
            remover(&(*p)->dir, x);
    }           
}

noPtr buscar(noPtr p, int x){
    if(p == NULL)
        return NULL;
    if(x == p->info)
        return p;
    if(x < p->info)
        return buscar(p->esq, x);
    else   
        return buscar(p->dir, x);
}

noPtr maior(noPtr *p){
    noPtr t;
    t = *p;
    if(t->dir == NULL){
        *p = (*p)->esq;
        return(t);
    }else   
        return(maior(&(*p)->dir));
}

bool enderecoVazio(notPtr p){
    if(p == NULL)
        return true;
    else    
        returne false;
}

void listarEmOrdem(noPtr p){
    if(!enderecoVazio(p)){
        listarEmOrdem(p->esq);
        cout << "\t" << p->info;
        listarEmOrdem(p->dir);
    }
}

void listarPreOrdem(noPtr p){
    if(!enderecoVazio){
        cout << "\t" << p->info;
        listarPreOrdem(p->esq);
        listarPreOrdem(p->dir);
    }
}

void listarPosOrdem(noPtr p){
    if(!enderecoVazio(p)){
        listarPosOrdem(p->esq);
        listarPosOrdem(p->dir);
        cout << "\t" << p->info;
    }
}

int menu(){
    int opcao;
    cout << "\n\n\n---- Menu Principal ----\n\n"
         << "\n1.Inserir no na arvore"
         << "\n2.Remover no na arvore"
         << "\n3.Listar todos os nos da arvore"
         << "\n4.Buscar no"
         << "\n0.Sair"
         << "\nDigite uma opcao: ";
    cin >> opcao;
    eturn opcao;
}

int listarNos(){
    int opcao;
    cout << "\n\nTipos de listagem:"
         << "\n1.Em Ordem"
         << "\n2.Pre Ordem"
         << "\n3.Pos Ordem"
         << "\n\nEscolha o tipo de listagem: ";
    cin >> opcao;
    return opcao;
}

main(){
    int op1, op2, x; 
    noPtr raiz = NULL;
    do {
        op1 = menu();
        switch(op1) {
        case 1: cout << "\nElemento a inserir: ";
            cin >> x; 
            inserir(&raiz, x); 
            break;

        case 2: cout << "\nElemento para remover: ";
            cin >> x; 
            remover (&raiz, x); 
            break;
        
        case 3: op2 = listarNos();
            if (op2 == 1) listarEmOrdem(raiz);
            if (op2 == 2) listarPreOrdem(raiz);
            if (op2 == 3) listarPosOrdem(raiz); 
            break;
        case 4: if (!enderecoVazio(raiz)) {
            cout << "\nElemento para buscar: ";
            cin >> x;
            noPtr p = buscar(raiz, x); 
            if (!p)
                cout << "\nElemento nao encontrado";
            else
                cout << "\nO elemento : " 
                << x 
                <<" foi encontrado no endereco:" 
                << p << "\n";
            } 
            else
            cout << "\nArvore vazia";
        }
    } while(op1 != 0);
}
