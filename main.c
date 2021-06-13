#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

// Nós representam as cidades
// Arestas representam as rodovias
// Matriz de adjacência

// Fazer 20 casos de teste em um .txt
/*
* Cada um com
* taxa de proporção do lucro desejado P
* nº de cidades a ser considerada N (5<=N<=20)
* nº de ligações rodoviárias E (0<=E<=9900)
* taxa de lucro esperada T (1<=T<=100)
* matriz adjacente que representa a ligação rodoviária direta entre duas cidades e contem as despesas e receitas desta ligação
*/

// O programa deve imprimir um relatório com o nº de caso se existe rota cíclica, quantas rotas cíclicas existem e qual a relação do lucro T e do valor P desejado. Imprimir o resultado em outro .txt


// Resumindo:

/*
* Coleta do arquivo os casos de teste
* Manipular os dados dos casos de teste para encontrar ciclo e encontrar o(s) ciclo(s) de menor custo
* Imprimir o relatório com o nº de casos, se existe rota cíclica e seu respectivo nº e a relação do lucro e valor P considerado
*/

#define MAX_CIDADES 20

typedef struct caminho{
	Pilha *p;
	float prop;
	struct caminho *prox;
}Caminho;




// Funções Lista

void printCaminho(Caminho *c){
	for(Caminho *i = c; i != NULL; i = i->prox){
		printPilha(i->p);
		printf("\n%.2f\n\n",i->prop);
	}
}

// Insere o registro de um ciclo
void insere_caminho(Caminho **L, Pilha *no, float proporcao){
	int i = no->i;
	Caminho *novo = malloc(sizeof(Caminho));
	if(!novo){
		printf("\nErro na alocação do caminho");
		exit(1);
	}
	pop(&no); // Retira o último para que não haja repetições de aresta
	novo->p = malloc(sizeof(Pilha)); ////////////////////////////////////////////////TODO
	novo->p = no;
	novo->prop = proporcao;
	novo->prox = *L;
	*L = novo;
	push(&no,i);
}

// Remoção dos nós da lista
void remove_caminhos(Caminho **L){
	Caminho *aux = *L, *aux2;
	Pilha *p1;
	for(; aux != NULL; aux = aux->prox){
		while(p1) // Desaloca todos os nós da pilha
			pop(&p1);
		aux2 = aux->prox;
		free(aux); // Para desalocar um nó da lista
		aux = aux2;
	}
	*L = NULL;
}

// Verifica se ciclo descoberto já é existente na lista
bool caminho_repetido(Caminho *C, Pilha *p){
	for(Caminho *aux = C; aux != NULL; aux = aux->prox)
		if(compara_pilha(p,aux->p))
			return true;
	return false;
}

// Desaloca as listas internas e zera a quantidade de caminhos de cada vértice da matriz
void zera_matriz(float MA[][20], int tam){
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			MA[i][j] = -1.0;
		}
	}
}

int conta_ciclos(Caminho *caminhos){
	int c = 0;
	for(Caminho *i = caminhos; i != NULL; i = i->prox){
		c++;
	}
	return c;
}

//Retorna a melhor proporcao dentre os ciclos
float melhor_proporcao(Caminho *caminhos){

	float melhorProp=0.0;
	while(caminhos){
		melhorProp = caminhos->prop ? melhorProp < caminhos->prop : melhorProp;
		caminhos = caminhos->prox;
	}

	return melhorProp;
}

// Exibe os resultados e grava em um arquivo txt
void resultados(Caminho *caminhos, float P_arq, int n_caso){
	FILE *resultado;
	int res, n_ciclos = conta_ciclos(caminhos);
	float P;
	P=melhor_proporcao(caminhos) / P_arq;

	printf("\n\nCaso número %d\n%2d Rotas cíclicas\nProporção de lucro %.2f\n\n", n_caso,n_ciclos, P);
	resultado = fopen("resultados.txt","a");
	if(!resultado){
		printf("Falha ao abrir/criar o arquivo");
		exit(1);
	}
	res = fprintf(resultado,"Caso número %d\n%2d Rotas cíclicas\nProporção de lucro %.2f\n\n\n", n_caso,n_ciclos, P);
	if(res == EOF){
		printf("\n\nErro na gravação dos dados no arquivo\n");
		exit(1);
	}
	fclose(resultado);
}

// Exibe a matriz de adjacência para testes
void print_matriz(float MA[][20], int tam){
	printf("\n\n     ");
	for(int i = 0; i < tam; i++)
		printf("  %2d  ", i);
	printf("\n");
	for(int i = 0; i < tam; i++){
		printf("%2d   ", i);
		for(int j = 0; j < tam; j++)
			printf("%5.2f ", MA[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

// Pode retornar se houve ciclo / custo do ciclo / vetor com os vértices do ciclo
void encontra_ciclo(float MA[][20], int tam,Caminho **listaCaminhos){
	// 1 Inicialize L como uma pilha vazia e uma estrutura para armazenar os caminhos
	int i,j,k;
	float propP = 0.0;
	Pilha *topo = inicializa();
	//Caminho *caminhos = *listaCaminhos;
	// 2 Insira o nó atual na pilha e verifique se o nó é igual ao início da pilha, se for igual, há um ciclo fechado (guarda o caminho*** e verifica a proporção), senão verifica se algum outro nó da pilha é igual, se for igual, ciclo aberto, retira o nó (descontar a proporção) e parte para outro, senão continua o algoritmo
	for(i = 0; i < tam; i++){ // Loop dos vértices

		push(&topo, i);
		// printf("push %d",i);
		// printPilha(topo);
		k = i;
		j = 0;
		propP = MA[i][j];

		while(topo != NULL){
			for(; j < tam; j++){ // 3 Dentro do nó, verifique se há algum arco de saída, se sim, vá para o passo 4, senão pule para o passo 5
				if(MA[k][j] > -1.0){ // 4 Escolha um arco de saída e siga para obter o próximo nó atual

					push(&topo, j);
					//printf("push  %d",j);
					//printPilha(topo);
					propP += MA[k][j];
					// Verifica o vértice inserido na pilha se existe
					switch(verifica(topo,j)){
						case 1: // Ciclo fechado: verifica se existe o caminho, se não existir salvar caminho, se existir, retira o nó da pilha
							//printf("\n\n________Ciclo fechado encontrado________\n\n");
							if(!caminho_repetido(*listaCaminhos,topo)){ //*** Verifica se existe o caminho antes de guardar
								//Adiciona na lista o caminho, se não for repetido
								insere_caminho(&(*listaCaminhos),topo,propP);
								printf("Ciclo inserido");
							}
							// Se existe, retira o vértice e continua
							propP -= MA[k][j];
							j = topo->i + 1;
							pop(&topo);
							if(!topo)
								break;
							k = topo->i;
							break;
						case -1: // Ciclo aberto (caminho com o ciclo + vértices iniciais), retira o nó que acabou de ser inserido, se for a base o algoritmo acaba as interações para este vértice
							//printf("\n\n__________Ciclo aberto encontrado___________\n\n");
							propP -= MA[k][j];
							j = topo->i + 1;
							pop(&topo);
							if(!topo)
								break;
							k = topo->i;
							break;
						default: // Não houve repetições, continua normalmente
							k = j;
							j = 0;
					}
					if(!topo)
						break;
				}
			}
			if(!topo)
				break;
			propP -= MA[k][j]; // 5 O final foi alcançado, remova o nó e volte para o anterior, se for o nó inicial não há ciclos e o algoritmo terminará
			j = topo->i + 1;
			pop(&topo);
			if(topo != NULL)
				k = topo->i;
		}
	}
}


int main(int argc, char **argv){

	// Matriz de adjacência
	float MA[MAX_CIDADES][MAX_CIDADES];


	// Leitura do arquivo de casos de teste
	FILE *casos_de_teste;
	int n_caso,proporcaoP,n_cidades,n_caminhos;
	int orig,dest,lucro,desp;
	// Variáveis para manipulação do grafo
	int n_ciclos;
	float proporcaoG;
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
	while(fscanf(casos_de_teste,"%d\n%d\n%d\n%d\n",&n_caso,&proporcaoP,&n_cidades,&n_caminhos) != EOF){
		// Pega a primeira linha <n_caso>
		// Pega a proporcao P
		// Pega a quantidade de cidades (vertices)
		// Pega a quantidade de caminhos (arestas) entre as cidades (vertices)

		// Prepara a matriz para alocar o grafo
		zera_matriz(MA,MAX_CIDADES);

		// Aloca as posições na matriz

		for(int c=0;c<n_caminhos;c++){
			fscanf(casos_de_teste,"%d %d %d %d\n",&orig,&dest,&lucro,&desp); // Pra cada caminho(aresta) pega: origem,destino,lucro, despesa
			if(MA[orig][dest] < (float) lucro / desp)
				MA[orig][dest] = (float) lucro / desp;
		}

		// Para testes
		print_matriz(MA,n_cidades);


		// Algoritmo de busca de ciclo (loop entre os vértices? Pode retornar se encontrou ciclo (problema de duplicidade) ou o lucro do ciclo)
		encontra_ciclo(MA, n_cidades, &caminhos);

		printCaminho(caminhos);
		resultados(caminhos, proporcaoP, n_caso);
		remove_caminhos(&caminhos);
	}

	fclose(casos_de_teste);
	return 0;
}