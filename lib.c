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

No *busca_no(No **p, int x) {
    if((*p) == NULL) {
        puts("Parametro invalido.");
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
    No *q, *tmp;

    if((*p) == NULL) return 1;

    q = (*p)->esq;
    tmp = q->dir;
    q->dir = (*p);
    (*p)->esq = tmp;
    (*p) = q;

    return 0;
}

int rot_esq(No **p) {
    No *q, *tmp;

    if((*p) == NULL) return 1;

    q = (*p)->dir;
    tmp = q->esq;
    q->esq = (*p);
    (*p)->dir = tmp;
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
