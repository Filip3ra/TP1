#pragma once
#include <vector>

class Graph
{
private:
  int N; // Número de vértices do grafo
  std::vector<std::vector<int>> adj;

public:
  Graph(int n);
  void addEdge(int a, int b);
  void printGraph();
  void initializeGraph(Graph &g);
};