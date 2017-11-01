#include <stdio.h>
#include <stdlib.h>
typedef struct reg* arestas;
typedef struct no* vertice;
typedef struct graf* grafo; 

typedef struct reg{
	int distancia;
	arestas proximaAresta;
	vertice verticeVizinho;
	
}estruturaDeUmaAresta;

typedef struct no{
	int id;
	int marcado;
	arestas primeiraAresta;
	arestas ultimaAresta;
	vertice proximoNaOrdemDeInsercao;

}estruturaDeUmVertice;

typedef struct graf{
	int elementos;
	vertice primeiroVertice;
	vertice ultimoVertice;
}cabecalhoDeUmGrafo;

void startaGrafo(grafo *g){
	(*g) = (grafo) malloc (sizeof(struct graf));
	(*g)->primeiroVertice = NULL;	
	(*g)->ultimoVertice = NULL;
	(*g)->elementos = 0;
}

int criaVertice(grafo g,int id){
	if(existeVertice(g,id))	return 0;	
	vertice p;
	p = (vertice) malloc(sizeof(struct no));
	p->id = id;
	p->marcado = 0;
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
	startaGrafo(&g);
	int i;
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
	printaGrafo(g);
	buscaEmProfundidade(g,1,1);
	printaGrafo(g);
	desmarcaGeral(g);
}

void buscaEmProfundidade(grafo g, int id, int n){	
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
}

