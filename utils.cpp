#include "utils.h"
#include <fstream>
#include <iostream>
#include <time.h>

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

void runTopologicalSorting(int type, Graph graph, int numberOfVertices, std::ofstream &dataFile)
{

  clock_t start = clock();
  type == 0 ? graph.topologicalSort() : graph.kahnTopologicalSort();
  clock_t end = clock();
  double interval = (double)(end - start) / CLOCKS_PER_SEC;

  dataFile << interval << " " << numberOfVertices << std::endl;
}