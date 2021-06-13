// Biblioteca Pilha

typedef struct pilha{
    int i;
    struct pilha *prox;
}Pilha;



void pop(Pilha **topo);
void push(Pilha **p, int vert);
Pilha* inicializa();
int verifica(Pilha *p, int vertice);
bool compara_pilha(Pilha *P1, Pilha *P2);
void printPilha(Pilha *p);
