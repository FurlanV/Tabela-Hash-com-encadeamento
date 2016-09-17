#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "Hash.h"

void inicializa(TLista *lista)
{
    lista->primeiro = (TCelula*)malloc(sizeof(TCelula));
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}

TCelula* alocaCelula()
{
    return (TCelula*)malloc(sizeof(TCelula));
}

void inserir(TLista *lista,TItem *item)
{
    TCelula *novaCelula;
    
    novaCelula = alocaCelula();
    novaCelula->item = *item;
    novaCelula->prox = NULL;
    
    lista->ultimo->prox  = novaCelula;
    lista->ultimo = novaCelula;
}

void imprimir(TLista *lista)
{
    TCelula *celulaAux;
    celulaAux = lista->primeiro->prox;
    
    while (celulaAux != NULL)
    {
        printf("nome: %s | codigo: %d\n",celulaAux->item.nome,celulaAux->item.codigo);
        celulaAux = celulaAux->prox;
    }
}

int pesquisar(TLista *lista,TItem *item)
{
    TCelula *celulaAux;
    
    celulaAux = lista->primeiro->prox;
    
    while(celulaAux != NULL){
        
        if(!strcmp(celulaAux->item.nome,item->nome)){
            *item =  celulaAux->item;
            return 1;
        }
    
        celulaAux = celulaAux->prox;
    }
    
    return 0;
}

void geraPesos(int p[])
{
  int i;
  struct timeval semente;

  gettimeofday(&semente,NULL);
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));

  for (i = 0; i < tamNome; i++)
     p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

unsigned int calculaH(TItem item, int p[])
{
    int i;
    unsigned int soma = 0;
        
    for(i=0; i<strlen(item.nome); i++)
        soma += (item.nome[i] * p[i]);
    
    
    return (soma%7);
}

void menu()
{
    FILE *arq;
    char caminhoArquivo[20];
    char nome[20];
    int codigo,i,opc=1;
    int p[tamNome];
    unsigned int h;
    
    TLista lista[tamTabela];
    TItem x;    
    
    geraPesos(p);
    
    for(i=0;i<tamTabela;i++)
        inicializa(&lista[i]);        
    
    printf("Digite o caminho inteiro para o arquivo:\n");
    scanf("%s",&caminhoArquivo);
    
    arq = fopen(caminhoArquivo,"r");
    
   if(arq){
       
       while(fscanf(arq,"%s %d\n",nome,&codigo)!= EOF){
          
           x.codigo = codigo;
           strcpy(x.nome,nome);
           
           h = calculaH(x,p);
          
           inserir(&lista[h],&x);

        }
       
       while(opc != 0){
           printf("\n1- Exibir tabela hash | 2- Pesquisar tripulante | 0- Sair\n");
           scanf("%d",&opc);
           
           switch(opc){
               case 1:
                   
                   for(i=0;i<tamTabela;i++)
                       imprimir(&lista[i]);
                   
                   break;
               case 2:
                   printf("Digite o nome que voce deseja pesquisar na lista\n");
                   scanf("%s",&x.nome);
                   
                   h = calculaH(x,p);
                   
                   if(pesquisar(&lista[h],&x) == 0)
                       printf("O tripulante '%s' nao viaja neste voo\n",x.nome);
                   else{
                       printf("O tripulante '%s' viaja neste voo !\n",x.nome);
                       printf("nome: %s | codigo: %d\n",x.nome,x.codigo);
                   }
                   break;
           }
       }
    }
   else
       printf("Erro ! Arquivo nao encontrado\n");
}
