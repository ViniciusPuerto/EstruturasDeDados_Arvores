typedef struct NO* ArvBin;

struct NO
{
    int info;
    struct NO *esq;
    struct NO *dir; 
};


ArvBin *raiz;

ArvBin* cria_ArvBin();

int checa_ArvVazia(ArvBin *raiz);

void libera_ArvBin(ArvBin *raiz);

int AlturaArvBin(ArvBin *raiz);

int TotalNos(ArvBin *raiz);

void preOrdemArvBin(ArvBin *raiz);

void emOrdemArvBin(ArvBin *raiz);

void posOrdemArvBin(ArvBin *raiz);

int insereArvBin(ArvBin *raiz, int valor);

int removeArvBin(ArvBin *raiz, int valor);

int consultaArvBin(ArvBin *raiz, int valor);