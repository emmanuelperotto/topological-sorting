/*
  Created by this sarradeiros:
    sarradation boy nº 1:
      Emmanuel Gustavo Rinaldi Perotto - 15/0124163
    sarradation boy nº 2:
      Lucas da Silva Moutinho - 15/0015747

  Thanks to our mothers that were there to put us in the world. We love You S2!!
*/

#include <fstream>
#include "graph.h"
#include "utils.h"

using namespace std;

// Function: main
// the main software function
// It:
//  - reads graph files with different vertices (10, 100, 10000, 100000)
//  - creates 4 graphs (with 10, 100, 10000 and 100000 vertices) with its edges
//  - executes the DFS topological sort algorithm and the Kahn Topological sort algorithm in each graph
//  - stores the time(seconds) vs node info in the results folder
//  - opens the graphic visualization with gnuplot
int main()
{
  int counter = 0;
  int nVertices, originVertex, destinyVertex;
  vector<string> files = {"graph-files/top_small.txt",
                          "graph-files/top_med.txt",
                          "graph-files/top_large.txt",
                          "graph-files/top_huge.txt"};
  vector<int> noVertices = {10,
                            100,
                            10000,
                            100000};
  ofstream dfsDataFile("results/dfs-data.txt");
  ofstream kahnDataFile("results/kahn-data.txt");

  for (string &fileName : files)
  {
    ifstream graphFile;
    graphFile.open(fileName);

    graphFile >> nVertices;
    Graph graph(nVertices);
    Graph graph2(nVertices);

    while (!graphFile.eof())
    {
      graphFile >> originVertex;
      graphFile >> destinyVertex;
      graph.addEdge(originVertex, destinyVertex);
      graph2.addEdge(originVertex, destinyVertex);
    }

    runTopologicalSorting(0, graph, dfsDataFile);
    runTopologicalSorting(1, graph2, kahnDataFile);

    counter++;
    graphFile.close();
  }

  dfsDataFile.close();
  kahnDataFile.close();

  initGraphicVisualization();

  cout << "=====================================================================================================================================" << endl;
  cout << "A conclusão sobre os resultados do gráfico podem ser encontrados no README.md" << endl;
  cout << "As ordenações topológicas se encontram na pasta raiz do projeto, com o seguinte formato: topological-order-<algoritmo>-<vertices>.txt" << endl;
  cout << "=====================================================================================================================================" << endl;
  return 0;
}
