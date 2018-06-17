#include "lib.h"

int main(void) {
    int i = 0;
    No *raiz = NULL;

    srand(time(NULL));

    for(i = 0; i < 5; i++) {
        insere_no(&raiz, i);
    }

    printf("Caminhamento Em-Ordem:\n");
    em_ordem(&raiz);

    remove_no(&raiz, 3);

    printf("Caminhamento Em-Ordem:\n");
    em_ordem(&raiz);


    return 0;
}
