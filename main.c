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

// Desaloca as listas internas e zera a quantidade de caminhos de cada vértice da matriz
void zera_matriz(float MA[][20], int tam){
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			MA[i][j] = -1.0;
		}
	}
}
// REVER
//solução que calcule o ciclo com maior proporção de lucro (Receitas totais / Despesas totais)
/*float calcula_prop(int receita, int despesa){
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
}*/

// Exibe os resultados e grava em um arquivo txt
void resultados(int ciclos, float P, int n_caso){
	FILE *resultado;
	int res;
	printf("\n\nCaso número %d\n%2d Rotas cíclicas\nProporção de lucro %.2f\n\n", n_caso,ciclos, P);
	resultado = fopen("resultados.txt","a");
	if(!resultado){
		printf("Falha ao abrir/criar o arquivo");
		exit(1);
	}
	res = fprintf(resultado,"Caso número %d\n%2d Rotas cíclicas\nProporção de lucro %.2f\n\n\n", n_caso,ciclos, P);
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
		printf("  %2d  ", i+1);
	printf("\n");
	for(int i = 0; i < tam; i++){
		printf("%2d   ", i+1);
		for(int j = 0; j < tam; j++)
			printf("%5.2f ", MA[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

// Pode retornar se houve ciclo / custo do ciclo / vetor com os vértices do ciclo
void encontra_ciclo(float MA[][20], int tam){
	// BFS
	// Floyd's tortoise and hare
}


int main(int argc, char **argv){


	float MA[MAX_CIDADES][MAX_CIDADES];


	//Leitura do arquivo de casos de teste
	FILE *casos_de_teste;
	int n_caso,proporcaoP,n_cidades,n_caminhos;
	int orig,dest,lucro,desp;
	// Variáveis para manipulação do grafo
	int n_ciclos;
	float proporcaoG;


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
		//Pega a quantidade de cidades (vertices)
		// Pega a quantidade de caminhos (arestas) entre as cidades (vertices)

		// Prepara a matriz para alocar o grafo
		zera_matriz(MA,20);

		// Aloca as posições na matriz

		for(int c=0;c<n_caminhos;c++){
			fscanf(casos_de_teste,"%d %d %d %d\n",&orig,&dest,&lucro,&desp); // Pra cada caminho(aresta) pega: origem,destino,lucro, despesa
			if(MA[orig][dest] < (float) lucro / desp)
				MA[orig][dest] = (float) lucro / desp;
		}

		// Para testes
		print_matriz(MA,n_cidades);

		n_ciclos = 0;
		proporcaoG = 0.0;

		// Algoritmo de busca de ciclo (loop entre os vértices? Pode retornar se encontrou ciclo (problema de duplicidade) ou o lucro do ciclo)
		encontra_ciclo(MA,n_cidades);



		resultados(n_ciclos, proporcaoG / proporcaoP, n_caso);
	}

	fclose(casos_de_teste);
	return 0;
}