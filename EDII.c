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
		printf("[%d]",p->dist->distancia );
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
	char resp;
	int id1,id2;
	int peso;
	do{

	printf("Qual operacao deseja relizar?\n");
	printf("1 - Criar vertice\n");
	printf("2 - Criar aresta simples\n");
	printf("3 - Criar aresta dupla\n");
	printf("4 - Busca em profundidade\n");
	printf("5 - Destra\n");
	printf("6 - ver grafo\n");
	do{
		resp = tolower(getch());
	}while(resp!='1' && resp!='2' && resp!='3' &&resp!='4' &&resp!='5' &&resp!='6')

	if(resp == '1'){
		printf("Digite o numero da aresta");
		scanf("%d",&id1);
		criaVertice(g,id1);
	}
	if(resp == '2'){
		printf("Digite o numero da origem");
		scanf("%d",&id1);
		printf("Digite o numero do destino");
		scanf("%d",&id2);
		printf("Digite o numero do peso");
		scanf("%d",&peso);
		arestaSimples(g,id1,id2,peso);
	}
	if(resp == '3'){
		printf("Digite o numero da origem");
		scanf("%d",&id1);
		printf("Digite o numero do destino");
		scanf("%d",&id2);
		printf("Digite o numero do peso");
		scanf("%d",&peso);
		arestaDupla(g,id1,id2,peso);	
	}
	if(resp == '4'){
		printf("Digite o numero da origem");
		scanf("%d",&id1);
		clear();
		printaGrafo(g);
		buscaEmProfundidade(g, id1,1);
		printaGrafo(g);
		getch();
		clear();
	}
	if(resp == '5'){
		printf("Digite o numero da origem");
		scanf("%d",&id1);
		dijikistra(g,id1);
		getch();
		clear();	
	}
	if(resp == '6'){
		printaGrafo(g);
	}
	/*for(i=0;i<=5;i++)
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
	buscaEmProfundidade(g,1,1);
	printaGrafo(g);
	desmarcaGeral(g);
	dijkstra(g);
	printaGrafo(g);
	*/
	printf("deseja reprocessar?(s/n)")
	do{
		resp = toupper(getch());
	}while(resp!='S'&&resp!='N');
	clear();
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

void dijkstra(grafo g, int id){
	distancias d;
	vertice p,q;
	distancias r,s;
	startaDistancias(g,d);
	vertice p,q,aux;
	aux = g->primeiroVertice;
	while(aux){
		if(aux->id == id)
			p = aux;
		aux = aux->proximoNaOrdemDeInsercao;
	}
	r = d;
	while(r->id!=id)	r = r->prox;
	r->distancia = 0; 
	distanciar(g,p);
	r = d;
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
		r = r->prox;
	}
	marca(r,1);
	r = proximaAresta;
	while(r){
		if(!(r->verticeVizinho->marcado))
		distanciar(g,r->verticeVizinho);
		r = r->proximaAresta;
	}

}

int startaDistancias(grafo g,distancias d){
	distancias nova,anterior;
	vertice p;
	p = g->primeiroVertice;
	nova = (distancias) malloc (sizeof(struct dij));
	nova->distancia = M;
	p->dist=nova;
	nova->id = p->id;
	nova->deOndeVeio = -1;
	nova->prox = NULL;
	d = nova;
	anterior = nova;
	p = p->proximoNaOrdemDeInsercao;
	while(p){
		nova = (distancias) malloc (sizeof(struct dij));
		nova->distancia = M;
		p->dist=nova;
		nova->id = p->id;
		nova->deOndeVeio = -1;
		nova->prox = NULL;
		anterior = nova;
		p = p->proximoNaOrdemDeInsercao;	
	} 
}