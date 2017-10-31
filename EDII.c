#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct reg* vertice;
typedef struct reg{
	int id;
	int visitado;
	int saidas;
	vertice saida[MAX];
	int peso[MAX];
}estruturaDeUmVertice;

typedef struct{
	int elementos;
	vertice elemento[MAX];
}grafo;

int CriaVertice(grafo g,int id){
	if(extisteVertice(g,id))	return 0;
	if(grafoCheio(g))	retun 0;
	vertice p;
	p = (vertice) malloc(sizeof(struct reg));
	p->id = id;
	p->visitado = 0;
	p->saidas = 0;
	g->elemento[g->elementos];
	g->elementos += 1;
}

int grafoCheio(grafo g){
	if(g->elementos == MAX) return 1;
	return 0;
}

int extisteVertice(grafo g,int id){
	for (int i = 0; i < g->elementos ; i++)
		if(id == g->elemento[i]->id) return 1;
	return 0;
}

int existeAresta(grafo g, vertice p, vertice q){
	for(i=0;i<p->saidas;i++)
		if(p->saida[i] == q) return 1;
	return 0;
}

int arestaSimples(grafo g, int id1, int id2, int peso){
	if(!existeVertice(g,id1)||!existeVertice(g,id2)) return 0;
	
	vertice p,q;
	int i=0;ok=0;
	while(ok!=2){
		if(g->elemento[i]->id==id1){
			ok++;
			p = g->elemento[i];		
		}
		if(g->elemento[i]->id == id2){
			ok++;
			q = g->elemento[i];		
		}
	}
	
	if(existeAresta(g,p,q)) return 1;
	
	p->peso[p->saidas];
	p->saida[p->saidas++]=q;
}

int arestaDupla(grafo g, int id1, int id2, int peso){
	return arestaSimples(g,id1,id2,peso)&&arestaSimples(g,id2,id1,peso);
}

void printaGrafo(grafo g){
	int i,j;
	for(i=0;i<g->elementos;i++){
		printf("%i -> ",g->elemento[i]->id)
		for(j=0;j<g->elemento[i]->saidas;j++)
			printf("%i - ",g->elemento[i]->saida[j]->id);
		printf("\n");
	}
}





















