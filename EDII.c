#include <stdio.h>
#include <stdlib.h>
#define M 999999999
typedef struct reg* arestas;
typedef struct no* vertice;
typedef struct graf* grafo;
typedef struct dij* distancias; 

typedef struct reg{
	int distancia;
	arestas proximaAresta;
	vertice verticeVizinho;
	
}estruturaDeUmaAresta;

typedef struct no{
	int id;
	int marcado;
	distancias dist;
	arestas primeiraAresta;
	arestas ultimaAresta;
	vertice proximoNaOrdemDeInsercao;

}estruturaDeUmVertice;

typedef struct graf{
	int elementos;
	vertice primeiroVertice;
	vertice ultimoVertice;
}cabecalhoDeUmGrafo;

typedef struct dij  {
	int distancia;
	int id;
	int deOndeVeio;
	distancias prox;
}cabecalhoDaListaDeDistanciasDijkstra;

void startaGrafo(grafo *g, distancias *d){
	(*g) = (grafo) malloc (sizeof(struct graf));
	(*g)->primeiroVertice = NULL;	
	(*g)->ultimoVertice = NULL;
	(*g)->elementos = 0;
	(*d)=NULL;
	
}

int criaVertice(grafo g,int id){
	if(existeVertice(g,id))	return 0;	
	vertice p;
	p = (vertice) malloc(sizeof(struct no));
	p->id = id;
	p->marcado = 0;
	p->dist = NULL;
	p->primeiraAresta = NULL;
	p->ultimaAresta = NULL;
	p->proximoNaOrdemDeInsercao = NULL;
	(g->elementos)++;
	if(!(g->primeiroVertice))
		g->primeiroVertice = g->ultimoVertice = p;
	else{
		g->ultimoVertice->proximoNaOrdemDeInsercao = p;
		g->ultimoVertice = p;		
	}
}

int existeVertice(grafo g, int id){
	vertice p;
	p = g->primeiroVertice;
	while(p){
		if(p->id==id) return 1;
		p = p->proximoNaOrdemDeInsercao;
	}
	return 0;
}

int existeAresta(grafo g, vertice p, vertice q){
	arestas k;
	k = p->primeiraAresta;
	while(k){
		if(k->verticeVizinho == q)	return 1;
		k = k->proximaAresta;
	}
	return 0;
}

int arestaSimples(grafo g, int id1, int id2, int distancia){
	if(!existeVertice(g,id1)||!existeVertice(g,id2)) return 0;
	vertice p,q,aux;
	int ok=2;
	aux = g->primeiroVertice;
	arestas nova;
	
	while(aux && ok){
		if(aux->id == id1){
			p = aux;
			ok--;
		}
		if(aux->id == id2){
			q = aux;
			ok--;
		}
		aux = aux->proximoNaOrdemDeInsercao;
	}
	if(existeAresta(g,p,q)) return 1;
	nova = (arestas) malloc (sizeof(struct reg));
	nova->verticeVizinho = q;
	nova->proximaAresta = NULL;
	nova->distancia=distancia;
	if(!(p->primeiraAresta)){
		p->primeiraAresta = nova;
		p->ultimaAresta = nova;
		return 1;
	}
	p->ultimaAresta->proximaAresta = nova;
	p->ultimaAresta = nova;
	return 1;
}

int arestaDupla(grafo g, int id1, int id2, int distancia){
	return arestaSimples(g,id1,id2,distancia)&&arestaSimples(g,id2,id1,distancia);
}

void marca(vertice p, int n){
	p->marcado = n;
}

void desmarcaGeral(grafo g){
	vertice p;
	p->id;
	p = g->primeiroVertice;
	while(p){
		p->marcado=0;
		p=p->proximoNaOrdemDeInsercao;
	}
}

void printaGrafo(grafo g){
	vertice p;
	arestas q;
	p = g->primeiroVertice;
	while(p){
		printf("%d",p->id);
		printf("(%d)",p->marcado);
//		if(p->dist->distancia == M)
//			printf("[sem ligacao]");
//		else
//		printf("[%d]",p->dist->distancia );
		printf(" -> ");
		q = p->primeiraAresta;
		while(q){
			printf("%d - ",q->verticeVizinho->id);
			q = q->proximaAresta;
		}
		printf("\n");
		p = p->proximoNaOrdemDeInsercao;
	}
	printf("\n\n");
}

int main(){
	grafo g;
	distancias d;
	startaGrafo(&g,&d);
	int i;
	char resp;
	int id1,id2;
	int peso;
	for(i=0;i<=5;i++)
		criaVertice(g, i);
	arestaSimples(g,1,5,1);
	arestaSimples(g,1,4,1);
	arestaSimples(g,1,3,1);
	arestaSimples(g,1,2,1);
	arestaSimples(g,2,3,1);
	arestaSimples(g,2,1,1);
	arestaSimples(g,3,4,1);
	arestaSimples(g,3,2,1);
	arestaSimples(g,3,1,1);
	arestaSimples(g,4,5,1);
	arestaSimples(g,4,3,1);
	arestaSimples(g,4,1,1);
	arestaSimples(g,5,4,1);	
	arestaSimples(g,5,1,1);
//	buscaEmProfundidade(g,1,1);
//	printaGrafo(g);
////	desmarcaGeral(g);
////	dijkstra(g);
//	printaGrafo(g);
//	
	do{
	system("CLS");
	printf("Qual operacao deseja relizar?\n");
	printf("1 - Criar vertice\n");
	printf("2 - Criar aresta simples\n");
	printf("3 - Criar aresta dupla\n");
	printf("4 - Busca em profundidade\n");
	printf("5 - Destra\n");
	printf("6 - ver grafo\n");
	do{
		resp = tolower(getch());
	}while(resp!='1' && resp!='2' && resp!='3' &&resp!='4' &&resp!='5' &&resp!='6');

	if(resp == '1'){
		printf("Digite o numero da aresta:\t");
		scanf("%d",&id1);
		criaVertice(g,id1);
	}
	if(resp == '2'){
		printf("Digite o numero da origem:\t");
		scanf("%d",&id1);
		printf("Digite o numero do destino:\t");
		scanf("%d",&id2);
		printf("Digite o do peso:\t");
		scanf("%d",&peso);
		arestaSimples(g,id1,id2,peso);
	}
	if(resp == '3'){
		printf("Digite o numero da origem:\t");
		scanf("%d",&id1);
		printf("Digite o numero do destino:\t");
		scanf("%d",&id2);
		printf("Digite o do peso:\t");
		scanf("%d",&peso);
		arestaDupla(g,id1,id2,peso);	
	}
	if(resp == '4'){
		printf("Digite o numero da origem:\t");
		scanf("%d",&id1);
		printaGrafo(g);
		buscaEmProfundidade(g, id1,1);
		printaGrafo(g);
	}
	if(resp == '5'){
		printf("Digite o numero da origem:\t");
		scanf("%d",&id1);
		printf("Digite o numero destino:\t");
		scanf("%d",&id2);
		dijkstra(g,id1,id2,&d);
	}
	if(resp == '6'){
		printaGrafo(g);
	}
	
	printf("deseja reprocessar?(s/n)\n");
	do{
		resp = toupper(getch());
	}while(resp!='S'&&resp!='N');
	}while(resp == 'S');
}

int buscaEmProfundidade(grafo g, int id, int n){	
	vertice p;
	arestas q;
//	if(existeVertice(g, id)) return 0;
	p = g->primeiroVertice;
	while(p->id!=id) p = p->proximoNaOrdemDeInsercao;
	
	marca(p,n);	
	q = p->primeiraAresta;
	while(q){
		if(!(q->verticeVizinho->marcado)){
			marca(q->verticeVizinho,n);
			buscaEmProfundidade(g,q->verticeVizinho->id,n+1);
		}
		q = q->proximaAresta;	 
	}
	return 1;
}


int dijkstra(grafo g, int id, int id2, distancias *d){
	int id1 = id2;
	int fica = 1;
	vertice p,q,aux;
	int i=0;
	int caminho[100];
	distancias r,s;
	startaDistancias(g,&(*d));
	aux = g->primeiroVertice;
	while(aux&&fica){
		if(aux->id == id){
			fica = 0;
			p = aux;
		}
		aux = aux->proximoNaOrdemDeInsercao;
	}
	r = *d;
	while(r->id!=id){
		r = r->prox;
	}	
	r->distancia = 0;
	distanciar(g,p);
	r = *d;
	printf("\nVertice[distancia] do vertice %d\n",id);
	while(r){
		if(r->distancia == M )
			printf("%d[N\\A] ",r->id);
		else
			printf("%d[%d] ",r->id,r->distancia);
		if(r->prox)
			printf(" - ");
		else
			printf("\n\n");
		r = r->prox;
		
	}
		aux = g->primeiroVertice;
	fica = 1;
	while(aux&&fica){
		if(aux->id == id2){
			caminho[++i] = id2;
			id2 = aux->dist->deOndeVeio; 
			fica = 0;
		}
		aux = aux->proximoNaOrdemDeInsercao;
	}
	while(id2!=-1){
		aux = g->primeiroVertice;
		fica = 1;
		while(aux){
		if(aux->id == id2){
			caminho[++i] = id2;
			id2 = aux->dist->deOndeVeio;
			fica = 0;
		}
		aux = aux->proximoNaOrdemDeInsercao;
		}	
	}
	printf("Melhor caminho de %d para %d:\n",id,id1);
	while(i){
		printf("%d  ",caminho[i--]);
	}
	printf("\n\n");	
}

int distanciar(grafo g, vertice p){
	vertice q;
	arestas r;
	distancias s;
	r = p->primeiraAresta;
	while(r){
		if(p->dist->distancia + r->distancia < r->verticeVizinho->dist->distancia){
			r->verticeVizinho->dist->distancia = p->dist->distancia + r->distancia;
			r->verticeVizinho->dist->deOndeVeio = p->id;
		}
		r = r->proximaAresta;
	}
	marca(p,1);
	r =  p->primeiraAresta;
	while(r){
		if(!(r->verticeVizinho->marcado))
		distanciar(g,r->verticeVizinho);
		r = r->proximaAresta;
	}
}

int startaDistancias(grafo g, distancias *d){
	distancias nova,anterior;
	vertice p;
	p = g->primeiroVertice;
	if(!(p->dist)){
	nova = (distancias) malloc (sizeof(struct dij));
	p->dist=nova;
	nova->id = p->id;
	nova->prox = NULL;
	if(!(*d))
	(*d) = nova;
	anterior = nova;
	}
	anterior = p->dist;
	anterior->distancia = M;
	anterior->deOndeVeio = -1;
	p->marcado = 0;
	p = p->proximoNaOrdemDeInsercao;
	while(p){
		if(!(p->dist)){
		nova = (distancias) malloc (sizeof(struct dij));
		p->dist=nova;
		nova->id = p->id;
		nova->prox = NULL;
		anterior->prox = nova;
		}
		anterior = p->dist;
		anterior->deOndeVeio = -1;
		anterior->distancia = M;
		p->marcado = 0;
		p = p->proximoNaOrdemDeInsercao;	
	} 	
}

