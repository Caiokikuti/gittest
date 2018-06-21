#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COL 10
#define MAX_LIN 10
#define ROSA 1
#define VERMELHO 2
#define AMARELO 3
#define AZUL 4

typedef struct tipo_item{
    int cor;
    int linha;
    int coluna;
}item;

typedef struct tipo_celula{
    struct tipo_item item;
    struct tipo_celula *prox;
}celula;

typedef struct tipo_fila{
    struct tipo_celula *primeiro;
    struct tipo_celula *ultimo;
}fila;

int vazia(fila *f){
    return f->primeiro->prox == NULL;
}

void inicializa(fila *f){
    f->primeiro=(celula *)malloc(sizeof(celula ));
    f->ultimo=f->primeiro;
    f->ultimo->prox=NULL;
}

void insere_fila(fila *f, int cor, int linha, int coluna){
    celula *novo = (celula*)malloc(sizeof(celula));
    novo->prox = f->ultimo->prox;
    novo->item.cor = cor;
    novo->item.linha = linha;
    novo->item.coluna = coluna;
    f->ultimo->prox = novo;
    f->ultimo = novo;
}

int remove_fila(fila *f, item *x){
    if(!vazia(f)){
        celula *aux;
        aux = f->primeiro->prox;
        f->primeiro->prox = aux->prox;
        *x = aux->item;
        free(aux);
        return 1;
    }else{
        return 0;
    }
}

int def_cor(int n){
    switch(n){
        case 0:
            return ROSA;
        case 1:
            return VERMELHO;
        case 2:
            return AMARELO;
        case 3:
            return AZUL;
        default:
            return 0;
    }
}

int criar(int i, int j, int matriz[MAX_LIN][MAX_COL]){
    srand(time(NULL));
    for(i = 0; i < MAX_COL; i++) {
        for (j = 0; j < MAX_LIN; j++) {
            matriz[i][j] = def_cor(rand() % 4);
        }
    }
}

void imprime_tabuleiro(int matriz[MAX_LIN][MAX_COL]){
    for(int i = 0; i < MAX_COL; i++){
        printf("%d| ", i);
        for(int j = 0; j < MAX_LIN; j++){
            printf("%d  ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int acima(int i,int j){
    if(i!=0) {
        return i-1;
    }else return -1;
}
int abaixo(int i, int j){
    if(i!= 9) {
        return i + 1;
    }else return -1;
}
int esquerda(int i, int j){
    if(j!=0) {
        return j - 1;
    }else return -1;
}
int direita(int i, int j){
    if(j!=9) {
        return j + 1;
    }else return -1;
}

void set_zero (int i, int j, int matriz[][MAX_COL], int flag) {
    int cor = matriz[i][j];
    if (cor != 0) {
        if (flag) {
            matriz[i][j] = 0;
        }
        if (acima(i, j) >= 0){
            if (cor == matriz[i - 1][j]){
                flag=1;
                set_zero(i - 1, j, matriz,flag);
            }
        }
        if (abaixo(i, j) >= 0){
            if (cor == matriz[i + 1][j]) {
                flag=1;
                set_zero(i + 1, j, matriz,flag);
            }
        }
        if (esquerda(i, j) >= 0){
            if (cor == matriz[i][j - 1]){
                flag =1;
                set_zero(i, j - 1, matriz, flag);
            }
        }
        if (direita(i, j) >= 0) {
            if (cor == matriz[i][j + 1]) {
                flag=1;
                set_zero(i, j + 1, matriz, flag);
            }
        }
    }
}


void remover(int matriz[MAX_LIN][MAX_COL], fila *f1){
    inicializa(f1);
    int novo_i = 9;
    int novo_j = 0;
    int flag = 0;
    for(int j = 0; j<10; j++){
        if(flag != 0){
            novo_j++;
        }
        flag = 0;
        novo_i = 9;
        for(int i = 9; i>=0; i--){
            if(matriz[i][j] != 0){
                insere_fila(f1, matriz[i][j], novo_i, novo_j);
                novo_i--;
                flag = 1;
            }
        }
    }
}

void print_matriz(int matriz[MAX_LIN][MAX_COL], fila *f1, item x){
    for(int i = 0; i<MAX_LIN; i++){
        for(int j = 0; j<MAX_COL; j++){
            matriz[i][j] = 0;
        }
    }
    while(!vazia(f1)){
        remove_fila(f1, &x);
        matriz[x.linha][x.coluna] = x.cor;
    }
    for(int i = 0; i<MAX_LIN; i++){
        printf("%d| ", i);
        for(int j = 0; j<MAX_COL; j++){
            printf("%d  ", matriz[i][j]);
        }
        printf("\n");
    }
}

void escreve(fila *f){
    celula *ptr=f->primeiro->prox;
    printf("=======================\n");
    while(ptr!=NULL){
        printf("cor: %d\nlinha: %d\ncoluna: %d\n\n",ptr->item.cor, ptr->item.linha, ptr->item.coluna);
        ptr=ptr->prox;
    }
    printf("=======================\n");
}

int controle_jogo(int matriz[MAX_LIN][MAX_COL]){
    int count = 0;
    int count1 = 0;
    int flag = 0;
    for(int i = 0; i < MAX_LIN; i++){
        for(int j = 0; j < MAX_COL; j++){
            if(matriz[i][j] != 0){
                if(acima(i, j) >= 0){
                    if (matriz[i][j] == matriz[i-1][j]){
                        count++;
                    }
                }
                if(abaixo(i, j) >= 0){
                    if (matriz[i][j] == matriz[i+1][j]){
                        count++;
                    }
                }
                if(esquerda(i, j) >= 0){
                    if (matriz[i][j] == matriz[i][j-1]){
                        count++;
                    }
                }
                if(direita(i, j) >= 0){
                    if (matriz[i][j] == matriz[i][j+1]){
                        count++;
                    }
                }
            }else{
                count1++;
            }
        }
    }
    if(count1 == 100){
        return 1;
    }
    if(count != 0){
        return 2;//jogo continua
    }
    if(count == 0){
        return 0;//PERDEEEEU
    }

}

int main(){
    fila fila1, fila2;
    item xiz;
    int matriz[MAX_LIN][MAX_COL];
    int linha, coluna;
    int controlador;
    inicializa(&fila1);
    inicializa(&fila2);



    criar(MAX_LIN, MAX_COL, matriz);
    printf("   0 |1 |2 |3 |4 |5 |6 |7 |8 |9|");
    printf("\n_______________________________\n");
    imprime_tabuleiro(matriz);

    do{
        printf("Linha: ");
        scanf("%d", &linha);
        printf("Coluna: ");
        scanf("%d", &coluna);
        set_zero(linha, coluna, matriz, 0);
        remover(matriz, &fila1);
        printf("   0 |1 |2 |3 |4 |5 |6 |7 |8 |9|");
        printf("\n_______________________________\n");
        print_matriz(matriz, &fila1, xiz);
        controlador = controle_jogo(matriz);
    }while(controlador == 2);

    if(controlador == 1){
        printf("PARABENS VOCE VENCEU!!");
    }
    if(controlador == 0){
        printf("VOCE PERDEU!!");
    }

    return 0;
}