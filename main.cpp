#include <iostream>

using namespace std;

class No { //declara classe No
public:
    int valor;
    int altura;
    No* esq;
    No* dir;

    No(int valor) {
        this->valor = valor;
        this->altura = 1;
        this->esq = NULL;
        this->dir = NULL;
    }
};

class AVL { //classe avl com no apontado pra raiz
    private:
    No* raiz;

    int altura(No* no){
        if(no == NULL){
            return 0;
        }
        return no->altura;
    }

    int FatorBalanceamento(No* no){ //fator de balanceamento entra a diferença da altura esq com altura dir
        if(no == NULL){
            return 0;
        }
        return altura(no->esq) - altura(no->dir);
    }

    //Rotações
    No* rotacaoDir(No* no){ //rotação a direita quando a subarvore esquerda esta mais pesada que a subarvore direita
        
        No* filhoEsq = no->esq; //aponta pra esq da raiz
        No* subArDir = filhoEsq->dir; //aponta pro filho a esq da raiz e a dir do filho

        //      50       35
        //     /        /  \
        //    35      20   50
        //   /   
        //  20    

        filhoEsq->dir = no; //no raiz fica a direita do filhoEsq
        no->esq = subArDir; //nova raiz a esq recebe a sub arvore direita do filho

        no->altura = max(altura(no->esq), altura(no->dir)) + 1;
        filhoEsq->altura = max(altura(filhoEsq->esq), altura(filhoEsq->dir)) +1;
        
        return filhoEsq;
    }

    No* rotacaoEsq(No* no){

        No* filhoDir = no->dir;
        No* subArEsq = filhoDir->esq;

        filhoDir->esq = no;
        no->dir = subArEsq;

        no->altura = max(altura(no->esq), altura(no->dir)) +1;
        filhoDir->altura = max(altura(filhoDir->esq), altura(filhoDir->dir)) +1;

        return filhoDir;

    }

    No* balancear(No* no) { //recebe um no e o balanceia se necessario. Se fatorbalanceamento == > 1 faz rotaçao a direita se for -1 faz rotaçao a esq
        if(no == NULL){
            return no;
        }

        no->altura = max(altura(no->esq), altura(no->dir)) +1;

        int fb = FatorBalanceamento(no);

        if(fb > 1 && FatorBalanceamento(no->esq) >= 0){
            return rotacaoDir(no);
        }
        if (fb > 1 && FatorBalanceamento(no->esq) < 0) {
            no->esq = rotacaoEsq(no->esq);
            return rotacaoDir(no);
        }
        if (fb < -1 && FatorBalanceamento(no->dir) <= 0) {
            return rotacaoEsq(no);
        }
        if (fb < -1 && FatorBalanceamento(no->dir) > 0) {
            no->dir = rotacaoDir(no->dir);
            return rotacaoEsq(no);
        }

        return no;
    }

    No* inserir(No* no, int valor) {
        if (no == NULL) {
            return new No(valor);
        }

        if (valor < no->valor) {
            no->esq = inserir(no->esq, valor);
        }
        else if (valor > no->valor) {
            no->dir = inserir(no->dir, valor);
        }
        else {
            return no;
        }

        return balancear(no);
    }

    No* procuraMin(No* no) { //retorna o no com valor min
        while (no->esq != NULL) {
            no = no->esq;
        }
        return no;
    }


    No* remove(No* no, int valor) { 
    if (no == NULL) {
        return no;
    }

    if (valor < no->valor) {
        no->esq = remove(no->esq, valor);
    }
    else if (valor > no->valor) {
        no->dir = remove(no->dir, valor);
    }
    else {
        if (no->esq == NULL && no->dir == NULL) {
            delete no;
            no = NULL;
        }
        else if (no->esq == NULL) {
            No* temp = no;
            no = no->dir;
            delete temp;
        }
        else if (no->dir == NULL) {
            No* temp = no;
            no = no->esq;
            delete temp;
        }
        else {
            No* temp = procuraMin(no->dir);
            no->valor = temp->valor;
            no->dir = remove(no->dir, temp->valor);
        }
    }

    if (no == NULL) {
        return no;
    }

    return balancear(no);
    }

}
