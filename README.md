# Rotas de viagem
Projeto utilizando matriz de adjacência de grafos para otimização de rotas de viagens de ônibus para maior lucro.
Projeto para a disciplina de Análise de Algoritmos e Teoria dos Grafos

## Descrição do problema

Uma agência de viagens, com intuito de lançar uma nova rota terrestre (ônibus) fez
uma pesquisa listando todas as estradas possíveis conectando diferentes cidades.

Nesta listagem, cada uma das estradas possui uma determinada receita com base na
tarifa atual. Entretanto, possui também, despesas associadas ao combustível, custo de
manutenção, pagamento de pessoal, impostos, etc.

A agencia de viagens deseja que o ônibus parte de uma cidade qualquer, visite uma ou
mais cidades, exatamente uma vez, e retorne para a cidade inicial, ou seja, uma rota
cíclica.

Os diretores desta agencia desejam somente rotas que tenham uma proporção de
lucro maior ou igual a P. A proporção de lucro para uma rota (P) é a proporção entre as
receitas totais e as despesas totais para esta rota

Um de seus amigos trabalha naquela empresa e pede uma ajudinha sua. Tudo que você
tem a fazer é determinar se existe tal rota, para que a empresa tem uma taxa de lucro
superior ou igual a P
Projeto

Cada caso é constituído pelos itens abaixo:
- A taxa de proporção do lucro desejado P
- Número de cidades a ser considerada N (5<= N <= 20)
- Número de ligações rodoviárias (estradas) E (0<= E <= 9900)
- Taxa de lucro esperada (1 <= P<= 100)
- Matriz Adjacente que representa a ligação rodoviária direta entre duas cidades e contem as despesas e receitas desta ligação

## Como executar

### Casos de teste
Os casos de teste são formatados em um arquivo `.txt`, da seguinte forma (somente números):
```
<Número do Caso>
<Proporção>
<Quantidade de vértices (Cidades)>
<Quantidade de arestas (Rotas, representadas pelas linhas abaixo)>
<Vértice origem> <Vértice destino> <Receita> <Despesa>
.
.
.

```



Para executar o algoritmo use o seguinte comando:

`make ; ./programa casos_de_teste.txt`

## Licença
Este projeto está licenciado pela MIT License, consulte [LICENSE](LICENSE) para mais informações

## Autores
- [Alcides Beato](https://github.com/alcidesbeato)
- [Henrique Siqueira](https://github.com/h-ssiqueira)
- [Iago Lourenço](https://github.com/iaglourenco)
- [Jemis Dievas](https://github.com/jamesdievas)
- [Rafael Barbon](https://github.com/RafaelBarbon)
