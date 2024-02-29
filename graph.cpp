#include "graph_header.hpp"
#include <iostream>

// Construtor
Graph::Graph(int n)
{
  this->N = n;
  adj.resize(n);
}

void Graph::addEdge(int a, int b)
{
  adj[a].push_back(b);
  // adj[b].push_back(a); // Comente essa linha se for um grafo direcionado
}

void Graph::printGraph()
{
  for (int v = 0; v < N; ++v)
  {
    std::cout << "[" << v << "]";
    for (unsigned x : adj[v]) //
      std::cout << " -> " << x;
    std::cout << std::endl;
  }
}

void Graph::initializeGraph(Graph &g)
{
  g.addEdge(0, 1);
  g.addEdge(0, 4);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 3);
  g.addEdge(3, 4);
}

/* Implementar um destrutor depois ? */
