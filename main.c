#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

/*
Nós representam as cidades
Arestas representam as rodovias
*/


#define MAX_CIDADES 20

// Estrutura que armazena os caminhos de ciclos e suas proporções
typedef struct caminho{
	Pilha *p; //Vertices do caminho
	double prop;// Proporcao do caminho
	struct caminho *prox;
}Caminho;


// Funções Lista

// Exibe o caminho do ciclo e sua respectiva proporção
int printCaminho(Caminho *c){
	int count=0;
	for(Caminho *i = c; i != NULL; i = i->prox){
		printPilha(i->p);
		printf("\n%.2lf\n\n",i->prop);
		count++;
	}
	return count;
}

// Insere o registro de um ciclo
void insere_caminho(Caminho **L, Pilha *no, double proporcao){
	Caminho *novo = calloc(1,sizeof(Caminho));
	if(!novo){
		printf("\nErro na alocação do caminho");
		exit(1);
	}
	novo->p = inicializa();
	for(Pilha *aux = no; aux != NULL; aux = aux->prox) // Copia a pilha (inversamente) para o caminho
		push(&novo->p, aux->i);
	novo->prop = proporcao;
	novo->prox = *L;
	*L = novo;
}

// Remoção dos nós da lista e desalocação dos mesmos
void remove_caminhos(Caminho **L){
	Caminho *aux = *L, *aux2;
	while(aux != NULL){
		while(pop(&aux->p)) // Desaloca todos os nós da pilha
			continue;
		aux2 = aux->prox;
		free(aux); // Para desalocar um nó da lista
		aux = aux2;
	}
	*L = NULL;
}

// Desaloca as listas internas e zera a quantidade de caminhos de cada vértice da matriz
void zera_matriz(double MA[][20], int tam){
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			MA[i][j] = -1.0;
		}
	}
}

// Retorna a melhor proporcao dentre os ciclos
// Calcula a quantidade de ciclos
double melhor_proporcao(Caminho *caminhos, int *ciclos){
	double melhorProp = 0.0;
	*ciclos = 0;
	while(caminhos){
		melhorProp = melhorProp < caminhos->prop ? caminhos->prop : melhorProp;
		(*ciclos)++;
		caminhos = caminhos->prox;
	}
	return melhorProp;
}

// Exibe os resultados e grava em um arquivo txt
bool resultados(Caminho *caminhos, double P_arq, int n_caso){
	FILE *resultado;
	int res, n_ciclos;
	double melhorProp = melhor_proporcao(caminhos,&n_ciclos);


	if(melhorProp >= P_arq){
		printf("\n\nCaso número %2d\n%3d Rotas cíclicas\nProporção de lucro desejada %.2lf\nMelhor proporção de lucro encontrada %.2lf\nRelação lucro encontrado com o esperado %.2lf\n", n_caso,n_ciclos, P_arq,melhorProp, melhorProp / P_arq);
		resultado = fopen("resultados.txt","a");
		if(!resultado){
			printf("Falha ao abrir/criar o arquivo");
			exit(1);
		}


		res = fprintf(resultado,"\n\nCaso número %2d\n%3d Rotas cíclicas\nProporção de lucro desejada %.2lf\nMelhor proporção de lucro encontrada %.2lf\nRelação lucro encontrado com o esperado %.2lf\n", n_caso,n_ciclos, P_arq,melhorProp, melhorProp / P_arq);
		if(res == EOF){
			printf("\n\nErro na gravação dos dados no arquivo\n");
			exit(1);
		}
		fclose(resultado);
		return true;
	}else{
		printf("\n\nCaso número %2d\nSem rotas cíclicas encontradas para a proporção de lucro desejada! (P=%.2lf) :(\n",n_caso,P_arq);
		resultado = fopen("resultados.txt","a");
		if(!resultado){
			printf("Falha ao abrir/criar o arquivo");
			exit(1);
		}

		int res = fprintf(resultado,"\n\nCaso número %2d\nSem rotas cíclicas encontradas para a proporção de lucro desejada! (P=%.2lf) :(\n",n_caso,P_arq);
		if(res == EOF){
			printf("\n\nErro na gravação dos dados no arquivo\n");
			exit(1);
		}
		fclose(resultado);
		return false;
	}

}

// Exibe a matriz de adjacência para testes
void print_matriz(double MA[][MAX_CIDADES], int tam){
	printf("\n\n     ");
	for(int i = 0; i < tam; i++)
		printf("  %2d  ", i);
	printf("\n");
	for(int i = 0; i < tam; i++){
		printf("%2d   ", i);
		for(int j = 0; j < tam; j++)
			printf("%.2lf ", MA[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

// Pode retornar se houve ciclo / custo do ciclo / vetor com os vértices do ciclo
void encontra_ciclos(double MA[][MAX_CIDADES], int tam,Caminho **listaCaminhos){
	// 1 Inicialize L como uma pilha vazia e uma estrutura para armazenar os caminhos
	int i,j,k/*,cont = 1,cont2=1,c*/;
	double propP = 0.0;
	Pilha *topo = inicializa();
	// 2 Insira o nó atual na pilha e verifique se o nó é igual ao início da pilha, se for igual, há um ciclo fechado (guarda o caminho*** e verifica a proporção), senão verifica se algum outro nó da pilha é igual, se for igual, ciclo aberto, retira o nó (descontar a proporção) e parte para outro, senão continua o algoritmo
	for(i = 0; i < tam; i++){ // Loop dos vértices
		push(&topo, i);
		/*printf("push %d",i);
		printPilha(topo);
		printf("\n\nInicia no V%d\n\n",i);
		cont2=0;
		c=0;*/
		k = i;
		j = 0;
		propP = 0.0;

		while(topo != NULL){
			for(; j < tam; j++){ // 3 Dentro do nó, verifique se há algum arco de saída, se sim, vá para o passo 4, senão pule para o passo 5
				if(MA[k][j] > -1.0){ // 4 Escolha um arco de saída e siga para obter o próximo nó atual

					push(&topo, j);
					/*
					// DEBUG
					printf("push  %d",j);
					printPilha(topo);
					printf("\n\n%d Proporcao= propAtual=%.2lf + MA=%.2lf\n",cont2,propP,MA[k][j]);
					printPilha(topo);
					cont2++; */

					// Verifica o vértice inserido na pilha se existe
					switch(verifica(topo,j)){
						case 1: // Ciclo fechado: verifica se existe o caminho, se não existir salvar caminho, se existir, retira o nó da pilha

							/*
							// DEBUG
							printf("\nCiclo fechado #%d________\n\n",cont);
							cont++;
							printPilha(topo);
							printf("\n_____________________________________\n\n");
							printf("\nLista de caminhos #%d_____________________________________\n\n",cont-1);
							printCaminho(*listaCaminhos);
							printf("\n_____________________________________\n\n"); */



							propP += MA[k][j];
							insere_caminho(&(*listaCaminhos),topo,propP); //Adiciona na lista o caminho
							// DEBUG
							// printf("Ciclo inserido");

							// Se existe, retira o vértice e continua
							propP -= MA[k][j];
							j = topo->i;
							pop(&topo);
							if(!topo) // Caso de loop no vértice
								break;
							k = topo->i;
							break;
						case -1: // Ciclo aberto (caminho com o ciclo + vértices iniciais), retira o nó que acabou de ser inserido, se for a base o algoritmo acaba as interações para este vértice

							/*
							// DEBUG
							printf("\n\n__________Ciclo aberto encontrado___________\n\n");
							printf("\n\nCiclo aberto #%d________\n\n",cont2);
							cont2++;
							printPilha(topo);
							printf("\n____________________________________\n\n"); */

							j = topo->i;
							pop(&topo);
							k = topo->i;
							break;
						case 0: // Não houve repetições, continua normalmente
							propP += MA[k][j];
							k = j;
							j = -1;
							break;
					}
					if(!topo) // Caso de loop no vértice
						break;
				}
			}
			if(!topo) // Caso de loop no vértice
				break;
			while(j == tam){ // Caso o novo topo da pilha seja o último vértice da matriz, o j não iria alcançar o for acima, executaria no máximo duas vezes: O(1)
				j = k;
				pop(&topo); // O final foi alcançado, remova o nó e volte para o anterior, se for o nó inicial não há ciclos e o algoritmo terminará
				if(!topo)
					break;
				k = topo->i;
				propP -= MA[k][j];
				j++;
			}
		}
	}
}

 //Mamain
int main(int argc, char **argv){

	// Matriz de adjacência
	double MA[MAX_CIDADES][MAX_CIDADES];


	// Leitura do arquivo de casos de teste
	FILE *casos_de_teste;
	int n_caso,n_cidades,n_caminhos;
	int orig,dest;
	double lucro,desp;
	// Variáveis para manipulação do grafo
	int n_ciclos;
	double proporcaoG,proporcaoP;
	Caminho *caminhos = NULL;


	if(argc != 2){
		printf("Parametros incorretos");
		exit(-1);
	}

	// Limpa os resultados da execução anterior se existirem
	casos_de_teste = fopen("resultados.txt","w");
	if(casos_de_teste)
		fclose(casos_de_teste);

	casos_de_teste = fopen(argv[1],"r");
	if(!casos_de_teste){
		printf("Falha ao abrir arquivo!");
		exit(-1);
	}

	//Ate o fim do arquivo
	while(fscanf(casos_de_teste,"%d\n%lf\n%d\n%d\n",&n_caso,&proporcaoP,&n_cidades,&n_caminhos) != EOF){
		// Pega a primeira linha <n_caso>
		// Pega a proporcao P
		// Pega a quantidade de cidades (vertices)
		// Pega a quantidade de caminhos (arestas) entre as cidades (vertices)

		// Prepara a matriz para alocar o grafo
		zera_matriz(MA,n_cidades);

		// Aloca as posições na matriz

		for(int c=0;c<n_caminhos;c++){
			fscanf(casos_de_teste,"%d %d %lf %lf\n",&orig,&dest,&lucro,&desp); // Pra cada caminho(aresta) pega: origem,destino,lucro, despesa
			if(MA[orig][dest] < (lucro / desp))
				MA[orig][dest] =  (lucro / desp);
		}

		// DEBUG
		// print_matriz(MA,n_cidades);

		// Algoritmo de busca de ciclo (loop entre os vértices? Pode retornar se encontrou ciclo (problema de duplicidade) ou o lucro do ciclo)
		encontra_ciclos(MA, n_cidades, &caminhos);

		resultados(caminhos, proporcaoP, n_caso);

		// DEBUG
		// printCaminho(caminhos);

		remove_caminhos(&caminhos);
	}



	fclose(casos_de_teste);
	return 0;
}
