#include <fstream>
#include "graph.h"
#include "utils.h"

using namespace std;

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

    while (!graphFile.eof())
    {
      graphFile >> originVertex;
      graphFile >> destinyVertex;
      graph.addEdge(originVertex, destinyVertex);
    }

    runTopologicalSorting(0, graph, noVertices[counter], dfsDataFile);
    runTopologicalSorting(1, graph, noVertices[counter], kahnDataFile);

    counter++;
    graphFile.close();
  }

  dfsDataFile.close();
  kahnDataFile.close();

  initGraphicVisualization();
  return 0;
}
