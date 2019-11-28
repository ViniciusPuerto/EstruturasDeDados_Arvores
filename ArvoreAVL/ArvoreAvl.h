typedef struct NO* ArvAvl;

ArvAvl *raiz;

ArvAvl* cria_ArvAvl();

int checa_ArvVazia(ArvAvl *raiz);

void libera_ArvAvl(ArvAvl *raiz);

int AlturaArvAvl(ArvAvl *raiz);

int TotalNos(ArvAvl *raiz);

int AltNo(struct NO *no);

int FatorBalanceamento_NO(struct NO *no);

void RotacaoLR(ArvAvl *raiz);

void RotacaoRL(ArvAvl *raiz);

void RotacaoRR(ArvAvl *raiz);

void RotacaoLL(ArvAvl *raiz);

int insertAvl(ArvAvl *raiz, int valor);

int RemoveNo(ArvAvl *raiz, int valor);

int insertAvl(ArvAvl *raiz, int valor);