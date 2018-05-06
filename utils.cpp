#include "utils.h"
#include <fstream>
#include <iostream>
#include <time.h>

// Function: initGraphicVisualization
// function to show DFS Topological Sort vs Kahn Topological Sort performance graphic
void initGraphicVisualization()
{
  FILE *fp;
  fp = popen("gnuplot -persist", "w");
  if (fp == NULL)
  {
    std::cout << "Error. Check if gnuplot is installed locally\n if not, run sudo apt install gnuplot-x11" << std::endl;
    return;
  }
  else
  {
    fprintf(fp, "set title 'Kahn vs DFS for topological sorting'\n");
    fprintf(fp, "set autoscale\n");
    fprintf(fp, "set xlabel 'Time(seconds)'\n");
    fprintf(fp, "set ylabel 'Nodes'\n");
    fprintf(fp, "plot 'results/kahn-data.txt' lt rgb '#E1802A' with lines smooth mcsplines, \
                      'results/dfs-data.txt' lt rgb '#773111' with lines smooth mcsplines\n");
  }
}

// Function: runTopologicalSorting
// function to run Topological Sort algorithms in a DAG graph
//
// Parameters:
//  - type: which algorithm will be used (0 for DFS and 1 for Kahn)
//  - graph: the DAG graph instance. (see <Graph>)
//  - dataFile: pointer to a previews opened ofstream file. This file will receive the number of vertices
//              from the graph and the execution time from the choosen algorithm

void runTopologicalSorting(int type, Graph graph, std::ofstream &dataFile)
{

  clock_t start = clock();
  type == 0 ? graph.topologicalSort() : graph.kahnTopologicalSort();
  clock_t end = clock();
  double interval = (double)(end - start) / CLOCKS_PER_SEC;

  dataFile << interval << " " << graph.getNVertices() << std::endl;
}