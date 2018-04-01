#include <stdio.h>
#include <stdlib.h>

struct no {
    int dado;
    struct no *proximo;
};

struct no* cria_no(int data) {
    struct no *pont1;
    pont1 = (struct no*)malloc(sizeof(struct no));
    pont1->dado = data;
    pont1->proximo = NULL;
    return pont1;
}

struct no* insere_no(struct no *root, int data) {
    struct no *novo_no = cria_no(data);
    struct no *pont2 = root;
    root = novo_no;
    novo_no->proximo = pont2;
    return root;
}

struct no* remover(struct no *pontx){
    struct no *boi=pontx;
    pontx=pontx->proximo;
    free(boi);
    return pontx;

};
void imprimir(struct no *raiz){
    struct no *p;
    for(p=raiz; p!=NULL; p=p->proximo){
        printf("%d\n", p->dado);
    }
}

int main () {

         struct no *raiz = NULL;
        imprimir(raiz);
        raiz = insere_no(raiz, 10);
        raiz = insere_no(raiz, 20);
        raiz = insere_no(raiz, 30);

        imprimir(raiz);

        raiz = remover(raiz);
        raiz = remover(raiz);

        printf("\n\n");
        imprimir(raiz);
}
