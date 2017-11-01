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
	int visitado;
	arestas primeiraAresta;
	arestas ultimaAresta;
	vertice proximoNaOrdemDeInsercao;

}estruturaDeUmVertice;

typedef struct graf{
	int elementos;
	vertice primeiroVertice;
	vertice ultimoVertice;
}cabecalhoDeUmGrafo;

void startaGrafo(grafo g){
	g = (grafo) malloc (sizeof(struct graf));
	g->primeiroVertice = NULL;	
	g->ultimoVertice = NULL;
	g->elementos = 0;
}

int criaVertice(grafo g,int id){
	printf("ok %d - 1\n",id);
	if(existeVertice(g,id))	return 0;	
	printf("ok %d - 2\n",id);
	vertice p;
	printf("ok %d - 3\n",id);
	p = (vertice) malloc(sizeof(struct no));
	printf("ok %d - 4\n",id);
	p->id = id;
	printf("ok %d - 5\n",id);
	p->visitado = 0;
	printf("ok %d - 6\n",id);
	p->primeiraAresta = NULL;
	printf("ok %d - 7\n",id);
	p->ultimaAresta = NULL;
	printf("ok %d - 8\n",id);
	p->proximoNaOrdemDeInsercao = NULL;
	printf("ok %d - 9\n",id);
//	(g->elementos)++;
	if(!(g->primeiroVertice))
		g->primeiroVertice = g->ultimoVertice = p;
	else{
		g->ultimoVertice->proximoNaOrdemDeInsercao = p;
		g->ultimoVertice = p;		
	}
	printf("ok %d - 10\n",id);

}

int existeVertice(grafo g,int id){
	vertice p;
	printf("??w");
	p = g->primeiroVertice;
	printf("??2");
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
	
	p->ultimaAresta->proximaAresta = nova;
	p->ultimaAresta = nova;
	nova->verticeVizinho = q;
	
	return 1;
}

int arestaDupla(grafo g, int id1, int id2, int distancia){
	return arestaSimples(g,id1,id2,distancia)&&arestaSimples(g,id2,id1,distancia);
}

void printaGrafo(grafo g){
	vertice p;
	arestas q;
	p = g->primeiroVertice;
	while(p){
		printf("\n");
		printf("%d -> ",p->id);
		q = p->primeiraAresta;
		while(q){
			printf("%d - ",q->verticeVizinho->id);
			q = q->proximaAresta;
		}
		p = p->proximoNaOrdemDeInsercao;
	}
}

int main(){
	grafo g;
	startaGrafo(g);
	int i;
	scanf("%d",&i);
	for(i=1;i<=10;i++)
		criaVertice(g, i);
		
	printaGrafo(g);
}










