#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"


//Remove elementos da pilha
bool pop(Pilha **topo){
    if(!*topo)
        return false;
    //Tira do topo da pilha
    Pilha *aux = (*topo)->prox, *aux2 = *topo;
    free(aux2);
    *topo = aux;
    return true;
}

//Adiciona elementos a pilha
void push(Pilha **p, int vert){
	Pilha *novo = calloc(1,sizeof(Pilha));
	if(!novo){
		printf("\nFalha ao alocar memória da pilha.");
		exit(1);
	}
	novo->prox = *p;
	novo->i = vert;
    *p = novo;
}

//Inicializa a pilha
Pilha* inicializa(){
	return NULL;
}

//Verifica se um vertice já está na pilha
//Retornos:
// -1: Vértice já existe e está no meio da pílha, possível ciclo interno
//  0: Vértice inexistente
//  1: Ciclo fechado encontrado
int verifica(Pilha *p, int vertice){
	Pilha *aux;
    if(p->prox == NULL) // Caso a pilha possuir apenas um elemento
        return 0;
	for(aux = p->prox; aux->prox != NULL; aux = aux->prox){ // Inicia no segundo elemento
		if(aux->i == vertice) // Verifica duplicidade no meio (ciclo aberto)
			return -1;
	}
    if(aux->i == vertice) // Verifica duplicidade na base (ciclo fechado)
		return 1;
    return 0; // Não possui duplicidades
}

// Printa a Pilha
// DEBUG
void printPilha(Pilha *p){
    printf("\n");
    for(Pilha *i = p; i != NULL; i = i->prox)
        printf("%d ", i->i);
    printf("\n");
}



