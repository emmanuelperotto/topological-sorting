#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>

class Graph
{
  int nVertices;

  // adjacency list
  std::list<int> *adj;

  // A function used by topologicalSort
  void topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack);

public:
  Graph(int nVertices);

  // function to add an edge to graph
  void addEdge(int originVertex, int destinyVertex);

  // DFS based topological sort
  void topologicalSort();
  // kahn's algorithm to topological sort
  void kahnTopologicalSort();
};

#endif