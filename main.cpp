#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;

class Graph
{
  int nVertices;

  // adjacency list
  list<int> *adj;

  // A function used by topologicalSort
  void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

public:
  Graph(int nVertices);

  // function to add an edge to graph
  void addEdge(int originVertex, int destinyVertex);

  // DFS based topological sort
  void topologicalSort();
  // kahn's algorithm to topological sort
  void kahnTopologicalSort();
};

Graph::Graph(int nVertices)
{
  this->nVertices = nVertices;
  adj = new list<int>[nVertices];
}

void Graph::addEdge(int originVertex, int destinyVertex)
{
  adj[originVertex].push_back(destinyVertex); // Add destinyVertex to originVertex’s list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int> &Stack)
{
  // Mark the current node as visited.
  visited[v] = true;

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      topologicalSortUtil(*i, visited, Stack);

  // Push current vertex to stack which stores result
  Stack.push(v);
}

// The DFS based function to do Topological Sort. It uses recursive
// topologicalSortUtil()
// https://www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSort()
{
  stack<int> Stack;

  // Mark all the vertices as not visited
  bool *visited = new bool[nVertices];
  for (int i = 0; i < nVertices; i++)
    visited[i] = false;

  // Call the recursive helper function to store Topological
  // Sort starting from all vertices one by one
  for (int i = 0; i < nVertices; i++)
    if (visited[i] == false)
      topologicalSortUtil(i, visited, Stack);

  // Print contents of stack
  while (Stack.empty() == false)
  {
    Stack.pop();
  }
}

// The kahn's algorithm function to do Topological Sort.
// https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
void Graph::kahnTopologicalSort()
{
  // Create a vector to store indegrees of all
  // vertices. Initialize all indegrees as 0.
  vector<int> in_degree(nVertices, 0);

  // Traverse adjacency lists to fill indegrees of
  // vertices.  This step takes O(V+E) time
  for (int u = 0; u < nVertices; u++)
  {
    list<int>::iterator itr;
    for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
      in_degree[*itr]++;
  }

  // Create an queue and enqueue all vertices with
  // indegree 0
  queue<int> q;
  for (int i = 0; i < nVertices; i++)
    if (in_degree[i] == 0)
      q.push(i);

  // Initialize count of visited vertices
  int cnt = 0;

  // Create a vector to store result (A topological
  // ordering of the vertices)
  vector<int> top_order;

  // One by one dequeue vertices from queue and enqueue
  // adjacents if indegree of adjacent becomes 0
  while (!q.empty())
  {
    // Extract front of queue (or perform dequeue)
    // and add it to topological order
    int u = q.front();
    q.pop();
    top_order.push_back(u);

    // Iterate through all its neighbouring nodes
    // of dequeued node u and decrease their in-degree
    // by 1
    list<int>::iterator itr;
    for (itr = adj[u].begin(); itr != adj[u].end(); itr++)

      // If in-degree becomes zero, add it to queue
      if (--in_degree[*itr] == 0)
        q.push(*itr);

    cnt++;
  }

  // Check if there was a cycle
  if (cnt != nVertices)
  {
    cout << "There exists a cycle in the graph\n";
    return;
  }

  // Print topological order
  // for (int i = 0; i < top_order.size(); i++)
  //   cout << top_order[i] << " ";
  // cout << endl;
}

void initGraphicVisualization()
{
  FILE *fp;
  fp = popen("gnuplot -persist", "w");
  if (fp == NULL)
  {
    cout << "Error. Check if gnuplot is installed locally\n if not, run sudo apt install gnuplot-x11" << endl;
    return;
  }
  else
  {
    fprintf(fp, "set title 'Kahn vs DFS for topological sorting'\n");
    fprintf(fp, "set autoscale\n");
    fprintf(fp, "set xlabel 'Time(seconds)'\n");
    fprintf(fp, "set ylabel 'Nodes'\n");
    fprintf(fp, "plot 'kahn-data.txt' lt rgb '#E1802A' with lines smooth mcsplines, \
                      'dfs-data.txt' lt rgb '#773111' with lines smooth mcsplines\n");
  }
}
int main()
{
  int counter = 0;
  int nVertices, originVertex, destinyVertex;
  vector<string> files = {"top_small.txt", "top_med.txt", "top_large.txt", "top_huge.txt"};
  vector<int> noVertices = {10,
                            100,
                            10000,
                            100000};
  ofstream kahnData("kahn-data.txt");
  ofstream dfsData("dfs-data.txt");

  for (string &fileName : files)
  {
    ifstream myFile;
    myFile.open(fileName);

    myFile >> nVertices;
    Graph graph1(nVertices);
    Graph graph2(nVertices);

    while (!myFile.eof())
    {
      myFile >> originVertex;
      myFile >> destinyVertex;
      graph1.addEdge(originVertex, destinyVertex);
      graph2.addEdge(originVertex, destinyVertex);
    }

    clock_t start = clock();
    graph1.topologicalSort();
    clock_t end = clock();
    double interval = (double)(end - start) / CLOCKS_PER_SEC;
    dfsData << interval << " " << noVertices[counter] << endl;

    clock_t startkahn = clock();
    graph2.kahnTopologicalSort();
    clock_t endkahn = clock();
    double intervalkahn = (double)(endkahn - startkahn) / CLOCKS_PER_SEC;
    kahnData << intervalkahn << " " << noVertices[counter] << endl;

    counter++;
    myFile.close();
  }

  kahnData.close();
  dfsData.close();

  initGraphicVisualization();
  return 0;
}
