#define tamNome 20
#define tamCod 8
#define tamTabela 7
#define ASCII_TAM 256

typedef struct{
    char nome[tamNome];
    int codigo;
}TItem;

typedef struct{
    TItem item;
    struct TCelula *prox;
}TCelula;

typedef struct{
    TCelula *primeiro;
    TCelula *ultimo;
}TLista;

TCelula* alocaCelula();
void inicializa(TLista *lista);
void inserir(TLista *lista,TItem *item);
void imprimir(TLista *lista);
int pesquisar(TLista *lista,TItem *item);
void geraPesos(int p[]);
unsigned int calculaH(TItem item, int p[]);



