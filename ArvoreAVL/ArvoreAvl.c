#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAvl.h"

struct NO{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};


ArvAvl* cria_ArvAvl(){
    ArvAvl* raiz = (ArvAvl*) malloc(sizeof(ArvAvl));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
};

int checa_ArvVazia(ArvAvl *raiz){
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
void libera_ArvAvl(ArvAvl *raiz){
    if (raiz == NULL)
    {
       return;
    }
    libera_NO(*raiz);
    free(raiz);

}

int AlturaArvAvl(ArvAvl *raiz){
    if (checa_ArvVazia(raiz))
        return 0;
    int alt_esq = AlturaArvAvl(&((*raiz)->esq));
    int alt_dir = AlturaArvAvl(&((*raiz)->dir));

    if (alt_esq > alt_dir){
        return alt_esq;
    }else{
        return alt_dir;
    }    
}

int TotalNos(ArvAvl *raiz){
   if (checa_ArvVazia(raiz))
        return 0;
    int alt_esq = AlturaArvAvl(&((*raiz)->esq));
    int alt_dir = AlturaArvAvl(&((*raiz)->dir));

    return (alt_esq + alt_dir + 1); 
}

int AltNo(struct NO *no){
    if (no == NULL)
    {
        return -1;
    }else
        return no->alt;
}

int FatorBalanceamento_NO(struct NO *no){
    return labs(AltNo(no->esq) - AltNo(no->dir));
};

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoLL(ArvAvl *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;

    (*raiz)->alt = maior(AltNo((*raiz)->esq), AltNo((*raiz)->dir) + 1);
    no->alt = maior(AltNo((*raiz)->alt) + 1 , AltNo(no->esq));
    *raiz = no;
    return;
}

void RotacaoRR(ArvAvl *raiz){
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;

    (*raiz)->alt = maior(AltNo((*raiz)->esq), AltNo((*raiz)->dir) + 1);
    no->alt = maior(AltNo((*raiz)->alt) + 1 , AltNo(no->dir));
    *raiz = no;
    return;
}

void RotacaoLR(ArvAvl *raiz){
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
    return;
}

void RotacaoRL(ArvAvl *raiz){
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
    return;
}

int insertAvl(ArvAvl *raiz, int valor){
    int res;
    if (*raiz == NULL){
        struct NO* novo;
        novo = (struct NO*)(malloc(sizeof(struct NO)));
        if (novo == NULL)
            return 0;
        novo->info = valor;
        novo->alt = 0;
        novo->dir = NULL;
        novo->esq = NULL;
        *raiz = novo;
        return 1;
    }
    struct NO* atual;
    atual = (struct NO*)(malloc(sizeof(struct NO)));
    struct No *atual = *raiz;
    if (valor < atual->info)
    {
        if ((res=insertAvl(&(atual->esq), valor)) == 1)
        {
            if (FatorBalanceamento_NO(atual) >= 2)
            {
                if (valor < (*raiz)->esq->info)
                {
                    RotacaoLL(raiz);
                }else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
            if (valor > atual->info){
                if ((res=insertAvl(&(atual->dir), valor)) == 1)
                    {
                        if (FatorBalanceamento_NO(atual) >= 2)
                        {
                            if ((*raiz)->dir->info < valor)
                            {
                                RotacaoRR(raiz);
                            }else
                            {
                                RotacaoRL(raiz);
                            }
                        }
                    }
            }else
            {
                printf("Valor duplicado!!!\n");
                return 0;
            }        
    }
    atual->alt = maior(AltNo(atual->esq), AltNo(atual->dir) + 1);
    return res;
};


int RemoveNo(ArvAvl *raiz, int valor){
   if (*raiz == NULL){
       printf("Valor inexiste!!\n");
       return 0;
   }

   int res;
   if (valor < (*raiz)->info){
        if ((res=insertAvl(&((*raiz)->esq), valor)) == 1){
                if (FatorBalanceamento_NO(*raiz) >= 2){
                    if (AltNo((*raiz)->dir->esq) < AltNo((*raiz)->dir->dir) ){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
    }else if(valor > (*raiz)->info){
        if((res=RemoveNo(&(*raiz)->dir,valor)) == 1){
            if(FatorBalanceamento_NO(*raiz) >= 2){
                if(AltNo((*raiz)->esq->dir) <= AltNo((*raiz)->esq->esq)){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else if(valor == (*raiz)->info){
        if( ((*raiz)->esq == NULL) || ((*raiz)->dir == NULL)){
            struct NO* oldNo;
            oldNo = (struct NO*)(malloc(sizeof(struct NO)));
            struct No *oldNo = *raiz;

            if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNo);
        }else{
            struct NO* temp;
            temp = (struct NO*)(malloc(sizeof(struct NO)));
            struct NO temp = procuraMenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            RemoveNo(&(*raiz)->dir, (*raiz)->info);
            if(FatorBalanceamento_NO(*raiz) >= 2){
                if(AltNo((*raiz)->esq->dir) <= AltNo((*raiz)->esq->esq)){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
        return 1;
        }
    return res;
}
    

struct NO procuraMenor(struct NO *atual){
    struct NO* no1 = atual;
    struct NO* no2 = atual->esq;
    while (no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return *no1;
}