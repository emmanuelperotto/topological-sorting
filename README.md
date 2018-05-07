# Topological sort in DAG graphs

The intuit of this project is to run two topological sort algorithms and compare its performance against different numbers of vertices.

# Running

You need gnuplot installed locally to run this project, if you don't have it type:

```
sudo apt install gnuplot-x11
```

Now go to the folder and type:

```
make run
```

or

```
make
make exec
```

# Resultados obtidos (OS RESULTADOS PODEM SER DIFERENTES DEPENDENDO DAS CONFIGURAÇÕES DA MÁQUINA)

Com o objetivo de determinar em quais circunstâncias qual dos algoritmos, DFS e Kahn, apresentava melhor performance, foram realizados testes utilizando duas máquinas diferentes rodando o algoritmo construído e gerando gráficos comparativos.

Observou-se que os gráficos gerados seguiam uma tendência; as curvas de tempo se invertiam a partir de um número X de vértices; ou seja, o algoritmo de kahn apresentava um menor tempo de execução para grafos com um menor número de vértices, enquanto que o DFS apresentava um menor tempo para grafos com um maior número de vértices. Para determinar qual o número X onde as curvas se encontravam, ou seja, a partir do qual o DFS passava a ter um menor tempo de execução, realizamos os testes em 2 máquinas diferentes, obtendo os seguintes resultados:

Os ponto X onde a performance dos algoritmos se igualavam foram:

* 5975, 2940
* 6800, 4300
* 1990, 6200
* 3151, 2600
* 3478, 7015

Que em média é:

* 4444.9 vértices

Com um desvio padrão de:

* 1786.014415

Concluí-se, portanto, que, em média, o algoritmo de Kahn apresenta melhor performance até 4.444 vértices com um desvio padrão de 1786 vértices.

Assim, para os grafos analisados, o melhor algoritmo é:

* 10 vértices: Kahn
* 100 vértices: Kahn
* 10000 vértices: DFS
* 100000 vértices: DFS