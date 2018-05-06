#include "graph.h"

// Constructor: Graph
// Initializes the object with number of vertices and alloc the adjacency list.
//
// Parameters:
//  - nVertices: the number of vertices (must be greater than 0)
Graph::Graph(int nVertices)
{
  this->nVertices = nVertices;
  adj = new std::list<int>[nVertices];
}

// Function: addEdge
// add an origin vertex to destiny vertex on DAG graph using the adjacency list.
//
// Parameters:
//    - originVertex: the start vertex
//    - destinyVertex: the end vertex
void Graph::addEdge(int originVertex, int destinyVertex)
{
  adj[originVertex].push_back(destinyVertex);
}

void Graph::topologicalSortUtil(int v, bool visited[],
                                std::stack<int> &Stack)
{
  // Mark the current node as visited.
  visited[v] = true;
  //

  //    - originVertex: the start vertexRecur for all the vertices adjacent to this ver
  //    - destinyVertex: the end vertex
  //
  // tex
  std::list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      topologicalSortUtil(*i, visited, Stack);

  // Push current vertex to stack which stores result
  Stack.push(v);
}

// Function: topologicalSort
// The DFS based function to do Topological Sort.
// reference: <https://www.geeksforgeeks.org/topological-sorting/>
void Graph::topologicalSort()
{
  std::stack<int> Stack;

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

// Function: kahnTopologicalSort
// The kahn's algorithm function to do Topological Sort.
// reference: <https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/>
void Graph::kahnTopologicalSort()
{
  // Create a vector to store indegrees of all
  // vertices. Initialize all indegrees as 0.
  std::vector<int> in_degree(nVertices, 0);

  // Traverse adjacency lists to fill indegrees of
  // vertices.  This step takes O(V+E) time
  for (int u = 0; u < nVertices; u++)
  {
    std::list<int>::iterator itr;
    for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
      in_degree[*itr]++;
  }

  // Create an queue and enqueue all vertices with
  // indegree 0
  std::queue<int> q;
  for (int i = 0; i < nVertices; i++)
    if (in_degree[i] == 0)
      q.push(i);

  // Initialize count of visited vertices
  int cnt = 0;

  // Create a vector to store result (A topological
  // ordering of the vertices)
  std::vector<int> top_order;

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
    std::list<int>::iterator itr;
    for (itr = adj[u].begin(); itr != adj[u].end(); itr++)

      // If in-degree becomes zero, add it to queue
      if (--in_degree[*itr] == 0)
        q.push(*itr);

    cnt++;
  }

  // Check if there was a cycle
  if (cnt != nVertices)
  {
    std::cout << "There exists a cycle in the graph\n";
    return;
  }

  // Print topological order
  for (int i = 0; i < top_order.size(); i++)
    std::cout << top_order[i] << " ";
  std::cout << std::endl;
}

// Function: getNVertices
// getter for number of vertices
//
// Returns:
//  - nVertices
int Graph::getNVertices()
{
  return this->nVertices;
}