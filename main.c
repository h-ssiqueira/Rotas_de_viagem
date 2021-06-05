#include <stdio.h>
#include <stdlib.h>

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

typedef struct aresta{
	int receita, despesa;
	struct aresta *prox;
}aresta;

typedef struct vertice{
	int num_arestas;
	aresta *conexoes;
}vert;

//Desaloca Grafo
void desaloca_grafo(aresta *lista){
	if(!lista)
		printf("\nLista Vazia");
	aresta *prox = NULL;
	while(lista->prox != NULL){
		prox = (lista)->prox;
		free(lista);
		lista = prox;
	}
}

// Insere um novo caminho entre duas cidades
void insere_aresta(aresta **lista, int receita, int despesa){
	aresta *novo = calloc(1,sizeof(aresta));
	novo->despesa = despesa;
	novo->receita = receita;
	novo->prox = NULL;
	if(!(*lista))
		*lista = novo;
	else{
		novo->prox = *lista;
		*lista = novo;
	}
}

// Desaloca as listas internas e zera a quantidade de caminhos de cada vértice da matriz
void zera_matriz(vert **MA, int tam){
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			if(MA[i][j].conexoes != NULL)
				desaloca_grafo(MA[i][j].conexoes);
			MA[i][j].num_arestas = 0;
		}
	}
}
//solução que calcule o ciclo com maior proporção de lucro (Receitas totais / Despesas totais)
float calcula_prop(aresta *A){
	float maior,des;
	if(A != NULL){
		maior = ((float)(A->receita) / A->despesa);
		while(A->prox != NULL){
			des = ((float)(A->receita) / A->despesa);
			if(des > maior)
				maior = des;
		}
	}
	return des;//Retorna maior porporção
}

// Exibe os resultados e grava em um arquivo txt
void resultados(int ciclos, int proporcaoP, int lucroP, int n_caso){
	FILE *resultado;
	int res;
	printf("\n\nCaso número %d\n%2d Rotas cíclicas\nProporção de lucro %.2f\n\n", n_caso,ciclos, lucroP / proporcaoP);
	resultado = fopen("resultados.txt","a");
	if(!resultado){
		printf("Falha ao abrir/criar o arquivo");
		exit(1);
	}
	res = fprintf(resultado,"Caso número %d\n%2d Rotas cíclicas\nProporção de lucro %.2f\n\n\n", n_caso,ciclos, lucroP / proporcaoP);
	if(res == EOF){
		printf("\n\nErro na gravação dos dados no arquivo\n");
		exit(1);
	}
	fclose(resultado);
}

void encontra_ciclo(vert **MA, int tam){
	// BFS
	// Floyd's tortoise and hare
}


int main(int argc, char **argv){


	vert MA[MAX_CIDADES][MAX_CIDADES];

	//Alocar matriz
	zera_matriz(MA,20);


	//Leitura do arquivo de casos de teste
	FILE *casos_de_teste;
	int n_caso,proporcaoP,n_cidades,n_caminhos;
	int orig,dest,lucro,desp;

	if(argc != 1){
		printf("Parametros incorretos");
		exit(-1);
	}

	casos_de_teste = fopen(argv[1],"r");
	if(!casos_de_teste){
		printf("Falha ao abrir arquivo!");
		exit(-1);
	}

	//Ate o fim do arquivo
	while(fscanf(casos_de_teste,"%d\n%d\n%d\n%d\n",&n_caso,&proporcaoP,&n_cidades,&n_caminhos) != EOF){
		// Pega a primeira linha <n_caso>
		// Pega a proporcao P
		//Pega a quantidade de cidades (vertices)
		// Pega a quantidade de caminhos (arestas) entre as cidades (vertices)



		// Aloca lista de arestas

		for(int c=0;c<n_caminhos;c++){
			fscanf(casos_de_teste,"%d %d %d %d\n",&orig,&dest,&lucro,&desp); // Pra cada caminho(aresta) pega: origem,destino,lucro, despesa
			MA[orig][dest].num_arestas+=1; //Incrementa quantidade de caminhos
			insere_aresta(MA[orig][dest].conexoes,lucro,desp); //Inserir aresta na lista da MA
		}



	return 0;
}