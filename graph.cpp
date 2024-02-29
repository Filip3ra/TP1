#include "graph_header.hpp"
#include <iostream>

Graph::Graph(int V)
{
  this->V = V;
  adj.resize(V);
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w);
  adj[w].push_back(v); // Uncomment this line if it's an undirected graph
}

void Graph::printGraph()
{
  for (int v = 0; v < V; ++v)
  {
    std::cout << "Adjacency list of vertex " << v << "\n";
    std::cout << "head";
    for (auto x : adj[v])
      std::cout << " -> " << x;
    std::cout << std::endl;
  }
}

void Graph::initializeGraph(Graph g)
{
  Graph g(5);
  g.addEdge(0, 1);
  g.addEdge(0, 4);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 3);
  g.addEdge(3, 4);

  g.printGraph();
}
