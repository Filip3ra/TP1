#pragma once
#include <vector>

class Graph
{
private:
  int V;
  std::vector<std::vector<int>> adj;

public:
  Graph(int V);
  void addEdge(int v, int w);
  void printGraph();
  void initializeGraph(Graph g);
};