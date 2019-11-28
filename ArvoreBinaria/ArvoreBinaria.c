#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
};

int checa_ArvVazia(ArvBin *raiz){
    if (*raiz == NULL){
        return 1;
    }
    return 0;
}

void libera_NO(struct NO *no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}
void libera_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
    {
       return;
    }
    libera_NO(*raiz);
    free(raiz);

}

int AlturaArvBin(ArvBin *raiz){
    if (checa_ArvVazia(raiz))
        return 0;
    int alt_esq = AlturaArvBin(&((*raiz)->esq));
    int alt_dir = AlturaArvBin(&((*raiz)->dir));

    if (alt_esq > alt_dir){
        return alt_esq;
    }else{
        return alt_dir;
    }    
}

int TotalNos(ArvBin *raiz){
   if (checa_ArvVazia(raiz))
        return 0;
    int alt_esq = AlturaArvBin(&((*raiz)->esq));
    int alt_dir = AlturaArvBin(&((*raiz)->dir));

    return (alt_esq + alt_dir + 1); 
}

void preOrdemArvBin(ArvBin *raiz){
     if (raiz == NULL){
       return;
    }
    if (*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        preOrdemArvBin(&((*raiz)->esq));
        preOrdemArvBin(&((*raiz)->dir));
    }
}

void emOrdemArvBin(ArvBin *raiz){
     if (raiz == NULL){
       return;
    }
    if (*raiz != NULL){
        emOrdemArvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdemArvBin(&((*raiz)->dir));
    }
}

void posOrdemArvBin(ArvBin *raiz){
     if (raiz == NULL){
       return;
    }
    if (*raiz != NULL){
        posOrdemArvBin(&((*raiz)->esq));
        posOrdemArvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}

int insereArvBin(ArvBin *raiz, int valor){
    if (raiz == NULL)
        return 0;

    struct NO* novo;
    novo = (struct NO*)(malloc(sizeof(struct NO)));
    if(novo == NULL)
        return 0;

    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if (*raiz == NULL){
        *raiz = novo;
    }else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while (atual != NULL){
            ant = atual;
            if (valor == atual->info){
                free(novo);
            }
            if(valor > atual->info){
                atual = atual->dir;
            }else
                atual = atual->esq;
        }
        if(valor > ant->info){
            ant->dir = novo;
        }else
            ant->esq = novo;
    }

    return 1;
}

int removeArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL) return 0;
    struct NO* atual = *raiz;
    struct NO* ant = NULL;
    while (atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz){
                *raiz = remove_atual(atual);
            }else
            {
                if (ant->dir == atual){
                    ant->dir = remove_atual(atual);
                }else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }

        ant = atual;
        if (valor > atual->info){
            atual = atual->dir;
        }else
            atual = atual->esq;
    }
    
};

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->esq;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }

    if (no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int consultaArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO *atual = *raiz;
    while (atual != NULL)
    {
        if (valor == atual->info)
        {
            return 1;
        }if (valor > atual->info)
        {
            atual = atual->dir;
        }else
            atual = atual->esq;
    }
    return 0;
};