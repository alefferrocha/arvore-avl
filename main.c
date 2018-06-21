#include "lib.h"

int main(void) {
    int i = 0;
    No *raiz = NULL;

    srand(time(NULL));

    for(i = 0; i < 7; i++) {
        insere_no(&raiz, i);
    }

    printf("Caminhamento Em-Ordem:\n");
    em_ordem(&raiz);
    printf("\n\n\nAltura %d \n\n", altura(&raiz));

    puts("Removendo chave [3]");
    delete(&raiz, 3);
    printf("Caminhamento Em-Ordem:\n");
    em_ordem(&raiz);
    printf("\n\n\nAltura %d \n\n", altura(&raiz));

    // puts("Removendo chave [3]");
    // delete(&raiz, 3);
    // printf("Caminhamento Em-Ordem:\n");
    // em_ordem(&raiz);
    // printf("\n\n\nAltura %d \n\n", altura(&raiz));

    return 0;
}
