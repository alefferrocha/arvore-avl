#include "lib.h"

int insere_no(No **p, int x) {
    int cresceu;

    // O no raiz esta vazio
    if(*p == NULL) {
        *p = (No *) malloc(sizeof(No));

        (*p)->chave = x;
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;

        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->chave >= x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu

        // puts("Chamando insereAVL (esquerda) again");
        cresceu = insere_no(&(*p)->esq, x);

        // Se cresceu for diferente de 0, logo a arvore cresceu
        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore direita era maior entao nao ha crescimento
                case 1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a subarvore direita tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = -1;
                    cresceu = 1;
                    break;
                // Se a subarvore da esquerda ja era maior entao deve-se re-balancear
                case -1:
                    if((*p)->esq->bal == -1) {
                        // Rotacao para a direita
                        rot_dir(p);
                        // Arruma os balanceamentos
                        (*p)->bal = (*p)->dir->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Rotaciona primeiro a esquerda
                        rot_esq(&(*p)->esq);
                        // Depois rotaciona a direita
                        rot_dir(p);
                        // Acerta balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    // Verifica se tem que inserir a direita
    else if((*p)->chave < x) {
        // Tenta inserir a direita e ve se a sub-arvore cresceu
        cresceu = insere_no(&(*p)->dir, x);

        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore esquerda era maior entao nao ha crescimento
                case -1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a arvore esquerda tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = 1;
                    cresceu = 1;
                    break;
                // Se a arvore da direita ja era maior entao deve-se re-balancear
                case 1:
                    // Verifica qual o caso de re-balanceamentos
                    if((*p)->dir->bal == 1) {
                        // Rotacao para a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        (*p)->bal = (*p)->esq->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Primeiro a direita
                        rot_dir(&(*p)->dir);
                        // Depois a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    else
        cresceu = 0;

    return cresceu;
}

No *transplanta_menor_direita(No **p, No **no_dir) {
    No *aux;

    if((*no_dir)->esq == NULL) {
        (*p)->chave = (*no_dir)->chave;
        aux = (*no_dir);
        (*no_dir) =  (*no_dir)->esq;
        return aux;
    }
    else {
        transplanta_menor_direita(&(*p), &(*no_dir)->esq);
    }
}

int remove_no(No **p, int x) {
    if((*p) == NULL) {
        puts("A arvore esta vazia.");
        return 0;
    }

    No *aux = (*p), *tmp = NULL, *pai = NULL;

    do {
        pai = aux;

        if(x < aux->chave)
            aux = aux->esq;
        else if (x >= aux->chave)
            aux = aux->dir;
    } while((aux != NULL) && (aux->chave != x));

    if(aux != NULL) {
        if((aux->esq != NULL) && (aux->dir != NULL)) {
            aux = transplanta_menor_direita(&aux, &aux->dir);

        }
        else if((aux->esq != NULL) && (aux->dir == NULL)) {
            if(pai->esq == aux)
                pai->esq = aux->esq;
            else
                pai->dir = aux->esq;
        }
        else if((aux->esq == NULL) && (aux->dir != NULL)) {
            if(pai->esq == aux)
                pai->esq = aux->dir;
            else
                pai->dir = aux->dir;
        }
        else{
            if(pai->esq == aux)
                pai->esq = NULL;
            else
                pai->dir = NULL;
        }

        free(aux);
    }

    return 1;
}

// No *bal_esq(No **p) {
//     No *filho_dir;
//     int bal_filho_dir, flag;
//
//     switch ((*p)->bal) {
//         case 1:
//             (*p)->bal = 0;
//             break;
//         case 0:
//             (*p)->bal = -1;
//             flag = 0;
//             break;
//         case -1:
//             filho_dir = (*p)->dir;
//             bal_filho_dir = filho_dir->bal;
//
//             if(bal_filho_dir <= 0) {
//                 rot_dir(p);
//
//                 if(bal_filho_dir == 0) {
//                     (*p)->bal = -1;
//                     filho_dir->bal = 1;
//                     flag = 0;
//                 }
//                 else {
//                     (*p)->bal = 0;
//                     filho_dir->bal = 0;
//                 }
//                 (*p) = filho_dir;
//             }
//             else {
//                 rot_esq(p);
//                 rot_dir(p);
//
//                 (*p)->bal = 0;
//             }
//     }
// }
//
// No *bal_dir(No **p) {
//     No *filho_esq;
//     int bal_filho_esq, flag;
//
//     switch ((*p)->bal) {
//         case -1:
//             (*p)->bal = 0;
//             break;
//         case 0:
//             (*p)->bal = 1;
//             flag = 0;
//             break;
//         case 1:
//             filho_esq = (*p)->esq;
//             bal_filho_esq = filho_esq->bal;
//
//             if(bal_filho_esq >= 0) {
//                 rot_esq(p);
//
//                 if(bal_filho_esq == 0) {
//                     (*p)->bal = 1;
//                     filho_esq->bal = -1;
//                     flag = 0;
//                 }
//                 else {
//                     (*p)->bal = 0;
//                     filho_esq->bal = 0;
//                 }
//                 (*p) = filho_esq;
//             }
//             else {
//                 rot_dir(p);
//                 rot_esq(p);
//
//                 (*p)->bal = 0;
//             }
//     }
// }

No *busca_no(No **p, int x) {
    if((*p) == NULL) {
        puts("A arvore esta vazia.");
        return NULL;
    }

    if((*p)->chave == x) {
        return (*p);
    }
    else {
        if((*p)->chave >= x) {
            return busca_no(&(*p)->dir, x);
        }
        else {
            return busca_no(&(*p)->esq, x);
        }
    }
}

int rot_dir(No **p) {
    No *q, *aux;

    if((*p) == NULL) return 1;

    q = (*p)->esq;
    aux = q->dir;
    q->dir = (*p);
    (*p)->esq = aux;
    (*p) = q;

    return 0;
}

int rot_esq(No **p) {
    No *q, *aux;

    if((*p) == NULL) return 1;

    q = (*p)->dir;
    aux = q->esq;
    q->esq = (*p);
    (*p)->dir = aux;
    (*p) = q;

    return 0;
}

void pre_ordem(No **p) {
    if((*p) != NULL){
        pre_ordem(&(*p)->esq);
        pre_ordem(&(*p)->dir);
        printf("%d\n", (*p)->chave);
    }
}

void em_ordem(No **p) {
    if((*p) != NULL){
        em_ordem(&(*p)->esq);
        printf("%d\n", (*p)->chave);
        em_ordem(&(*p)->dir);
    }
}

void pos_ordem(No **p) {
    if((*p) != NULL){
        printf("%d\n", (*p)->chave);
        pos_ordem(&(*p)->esq);
        pos_ordem(&(*p)->dir);
    }
}

int altura(No **p) {
    int alt_esq = 0, alt_dir = 0;

    if((*p) == NULL) {
        return -1;
    }
    else {
        alt_esq = altura(&(*p)->esq);
        alt_dir = altura(&(*p)->dir);

        if(alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}
