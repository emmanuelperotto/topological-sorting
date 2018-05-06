#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <iostream>
#include "graph.h"

void initGraphicVisualization();
void runTopologicalSorting(int type, Graph graph, std::ofstream &dataFile);

#endif