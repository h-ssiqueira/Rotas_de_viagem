// Biblioteca Pilha

typedef struct pilha{
    int i;
    struct pilha *prox;
}Pilha;



bool pop(Pilha **topo);
void push(Pilha **p, int vert);
Pilha* inicializa();
int verifica(Pilha *p, int vertice);
void printPilha(Pilha *p);
