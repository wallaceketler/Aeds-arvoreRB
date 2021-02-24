#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Record Record;
typedef struct No No;

struct Record
{
    char value[20];
    float key;
};

struct No
{
    bool color; //true = vermelho false = preto
    Record reg;
    No *esq;
    No *dir;
    No *pai;
};

No *CreateNo()
{
        return NULL;
}

void rotacaoEsq(No **item)
{
	No *aux;
	aux=(*item)->esq;
	(*item)->esq = aux->esq;
	aux->esq = (*item);
}

void rotacaoDir(No **item)
{
	No *aux;
	aux=(*item)->dir;
	(*item)->dir = aux->dir;
	aux->dir = (*item);
}

No* insertTree(No **raiz,No **pai, Record r)
{
    if(*raiz==NULL)
    {
        *raiz=(No*)malloc(sizeof(No));
        (*raiz)->esq=NULL;
        (*raiz)->esq=NULL;
        (*raiz)->reg=r;
        (*raiz)->color=true;
        (*raiz)->pai=*pai;
       	//printf("TESTEEEEE: %f", (*raiz)->reg.key);

      	return *raiz;
    }
    else
    {
	    if(r.key > (*raiz)->reg.key)
	    {
	    	*pai=*raiz;
	        insertTree(&(*raiz)->dir, &(*pai), r);
	      
	    }
	    if(r.key < (*raiz)->reg.key)
	    {
	    	*pai=*raiz;
	        insertTree(&(*raiz)->esq, &(*pai), r);
	    }
	}


}


int global=0;

void insertRB(No **raiz, No **pai, Record r)
{
	
	No *tio;
	No *aux;
	No *item;
	

	if(global==0)
	{
		aux=*raiz;
		global=1;
				printf("TESTEEEEE: %f", (*raiz)->reg.key);

	}
	if((*raiz)->reg.key==r.key && global!=2)
	{
		
		item=*raiz;
				printf("TESTEEEEE: %f", item->reg.key);

		global=2;
		insertRB(&(*raiz), &(*pai), r);

	}
	else
	{
		if(r.key > (*raiz)->reg.key)
			insertRB(&(*raiz)->dir, &(*pai), r);
		if(r.key < (*raiz)->reg.key)
			insertRB(&(*raiz)->esq, &(*pai), r);
	}

	if(global==2)
	{
		
		/*	
		while(((((*raiz)->reg.key)!=(aux)->reg.key)) &&(*raiz)->pai->color==true)
		{
			if((*raiz)->pai->reg.key == (*raiz)->pai->pai->esq->reg.key)
			{	
				tio = (*raiz)->pai->pai->dir;
				if(tio->color==true)
				{
					(*raiz)->pai->color=false;
					tio->color=false;
					(*raiz)->pai->pai->color=true;
					*raiz=(*raiz)->pai->pai;
				}
				
				else if((*raiz)->reg.key==(*raiz)->pai->dir->reg.key)
				{
					(*raiz)=(*raiz)->pai;
					rotacaoEsq(&(*raiz));
				}
				
				(*raiz)->pai->color=false;
				(*raiz)->pai->pai->color=true;
				rotacaoDir(&(*raiz)->pai->pai);
				
			}
			
			else
			{
				
				tio = (*raiz)->pai->pai->esq;
				if(tio->color==true)
				{
					(*raiz)->pai->color=false;
					tio->color=false;
					(*raiz)->pai->pai->color=true;
					(*raiz)=(*raiz)->pai->pai;
				}
				
				else if((*raiz)->reg.key==(*raiz)->pai->esq->reg.key)
				{
					*raiz=(*raiz)->pai;
					rotacaoEsq(&(*raiz));
				}
				
				(*raiz)->pai->color=false;
				(*raiz)->pai->pai->color=true;
				rotacaoDir(&(*raiz)->pai->pai);

			}
			
			
		}
		(aux)->color=false;
		*/
	}

}





void print2d2(No **raiz, int space)
{
	if(*raiz==NULL)
		return;
	int count=10;
	space = space+count;

	print2d2(&(*raiz)->dir, space);

	printf("\n");
	for(int i=count; i < space; i++)
	{
		printf(" ");
	}
	printf("%f\n", (*raiz)->reg.key);
	print2d2(&(*raiz)->esq, space);
}

void print2d(No **raiz, int space)
{
	print2d2(&(*raiz), 0);
}


void pesquisa(No **raiz, No **aux, Record r)
{

    if(*raiz==NULL)
    {
        printf("Valor não encontrado");
       	return;
    }
    if(r.key > (*raiz)->reg.key)
    {
        pesquisa(&(*raiz)->dir,aux, r);
        return;
    }
    if(r.key < (*raiz)->reg.key)
    {
        pesquisa(&(*raiz)->esq,aux,  r);
        return;
    }
    *aux = *raiz;
    if((*aux)->reg.key==r.key)
    {   
    	printf("Este corpo está presente\n");
    }

}

void emOrdem(No *raiz)
{
	if(raiz!=NULL)
	{
    	emOrdem(raiz->esq);
    	printf("%s : %f milhões de Km\n",raiz->reg.value, raiz->reg.key);
    	emOrdem(raiz->dir);
    }
}

void Antecessor(No **raiz, No *aux)
{
    if((*raiz)->dir!=NULL)
    {
        Antecessor(&(*raiz)->dir, aux);
        return;
    }

    aux->reg=(*raiz)->reg;
    aux=*raiz;
    *raiz=(*raiz)->esq;
    free(aux);
}

void removeNode(No **raiz, Record r)
{
    No *aux;

    if((*raiz)==NULL)
    {
        printf("Valor não encontrado");
        return;
    }
        
    if(r.key>(*raiz)->reg.key)
    {
       removeNode(&(*raiz)->dir,r);
       return;
    }
    if(r.key<(*raiz)->reg.key)
    {
        removeNode(&(*raiz)->esq, r);
        return;
    }

    if((*raiz)->dir==NULL)
    {
       aux = *raiz;
       *raiz = (*raiz)->esq;
       free(aux);
       return;
    }

    if((*raiz)->esq!=NULL)
    {
        Antecessor(&(*raiz)->esq, *raiz);
        return;
    }

    aux=*raiz;
    *raiz=(*raiz)->dir;
    free(aux);
}
    
int main()
{
    No *raiz;
    No *aux;
    No *pai;
    No *item;

    raiz=CreateNo();
    aux=CreateNo();

    Record r;
    int x=0;
    int op=0;
    char valor[20];
    float chave;
   	int contador=0;
   	int space=0;
 

    float vetKey[]={57.91, 108.2, 149.6, 227.9, 778.5, 1434, 2871, 4495};

	

    char vet1[20]="Mercurio";
    char vet2[20]="Venus";
    char vet3[20]="Terra";
    char vet4[20]="Marte";
    char vet5[20]="Jupiter";
    char vet6[20]="Saturno";
    char vet7[20]="Urano";
    char vet8[20]="Netuno";

    for(int i=0; i<8; i++)
    {
    	if(i==0)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet1[i];
    		}
    	}
    	if(i==1)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet2[i];
    		}
    	}
    	if(i==2)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet3[i];
    		}
    	}
    	if(i==3)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet4[i];
    		}
    	}
    	if(i==4)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet5[i];
    		}
    	}
    	if(i==5)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet6[i];
    		}
    	}
    	if(i==6)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet7[i];
    		}
    	}
    	if(i==7)
    	{
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=vet8[i];
    		}
    	}
    	global=0;
       	r.key=vetKey[i];
       	insertTree(&raiz, &pai, r);
        insertRB(&raiz, &pai, r);
    }

    printf("O sistema solar é constituído por 8 planetas, cada qual com certa distância ao Sol, a estrela na qual eles orbitam");
    printf("\n");
    printf("São eles: Terra, Marte, Saturno, Urano, Netuno, Júpiter, Vênus e Mercúrio\n");
    printf("Entretanto o universo é imenso, e podemos relacionar outros corpos celestes com o nosso Sol.\n");
    while(x==0)
    {
    	contador=0;
    	printf("Digite:");
    	printf("\n");
    	printf("[1] Para mostrar os corpos em ordem de distância ao Sol\n");
    	printf("[2] Para adicionar um novo corpo celeste\n");
    	printf("[3] Para remover algum corpo celeste que você adicionou\n");
    	printf("[4] Para saber se certo corpo está em nosso sistema espacial\n");
    	printf("[5] Para exibir, em árvore, os valores das distâncias\n");
    	printf("[6] Para sair\n");
    	scanf("%d", &op);
    	if(op==1)
    	{
    		emOrdem(raiz);
    	}
    	if(op==2)
    	{
    		printf("Digite o nome deste corpo\n");
    		scanf("%s", valor);
    		printf("Digite a distância deste corpo ao sol\n");
    		scanf("%f", &chave);
    		r.key=chave;
    		for(int i=0; i<20; i++)
    		{
    			r.value[i]=valor[i];
    		}
    	    insertTree(&raiz, &pai, r);
    		insertRB(&raiz, &pai, r);
    		
    	}
    	if(op==3)
    	{
    		printf("Digite o nome deste corpo\n");
    		scanf("%s", valor);
    		printf("Digite a distância deste corpo ao sol\n");
    		scanf("%f", &chave);

   
    			r.key=chave;
    			for(int i=0; i<20; i++)
    			{
    				r.value[i]=valor[i];
    			}
    			removeNode(&raiz, r);
   
    	}
    	if(op==4)
    	{
    		printf("Digite o nome deste corpo\n");
    		scanf("%s", valor);
    		printf("Digite a distância deste corpo ao Sol\n");
    		scanf("%f", &chave);
    		for(int i=0; i<20; i++)
    		{
    				r.value[i]=valor[i];
    		}
    		r.key=chave;
    		pesquisa(&raiz, &aux, r);
    	}
    	if(op==5)
    	{
    		print2d(&raiz, space);
    	}
    	if(op==6)
    	{
    		x=1;
    	}
    }
  
    return 0;
}
