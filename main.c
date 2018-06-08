#include "lib.h"

int main(void) {
    int i = 0;
    No *raiz = NULL;

    srand(time(NULL));

    for(i = 0; i < 2048; i++) {
        insere_no(&raiz, rand() % 500);
    }

    // printf("Altura da arvore: %d", altura(&raiz));
    // 
    //printf("Altura da arvore: %d\n", altura(&raiz));
    //
    // printf("Caminhamento Pre-Ordem:\n");
    // pre_ordem(&raiz);
    //
    // printf("Caminhamento Em-Ordem:\n");
    // em_ordem(&raiz);
    //
    // printf("Caminhamento Pos-Ordem:\n");
    // pos_ordem(&raiz);



    return 0;
}
