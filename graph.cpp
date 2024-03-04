#include "graph_header.hpp"
#include <iostream>
using namespace std;

// Construtor
Graph::Graph(int n)
{
  this->N = n;
  adjList.resize(n);
}

void Graph::addEdge(int a, int b, int weight)
{
  adjList[a].push_back(make_pair(b, weight)); // a---[b, weight]
}

void Graph::printGraph()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "]";
    for (auto x : adjList[v]) // "auto" Escolhe automaticamente o tipo de x
      cout << " --> {" << x.first << "," << x.second << "}";
    cout << endl;
  }
}

vector<int> Graph::calculateDegree()
{
  vector<int> degrees(N, 0); // Inicializa o vetor de graus com 0 para cada vértice
  for (int v = 0; v < N; ++v)
  {
    for (auto edge : adjList[v])
    {
      degrees[edge.first]++; // Incrementa o grau do vértice v para cada aresta incidente
    }
  }
  return degrees;
}

void Graph::initializeGraph(Graph &g)
{
  g.addEdge(0, 1, 0);
  g.addEdge(0, 2, 0);
  g.addEdge(0, 3, 0);
  g.addEdge(1, 4, 4);
  g.addEdge(1, 5, 4);
  g.addEdge(2, 4, 10);
  g.addEdge(2, 5, 10);
  g.addEdge(3, 2, 7);
  g.addEdge(3, 6, 7);
  g.addEdge(4, 7, 3);
  g.addEdge(5, 8, 1);
  g.addEdge(5, 9, 1);
  g.addEdge(6, 11, 8);
  g.addEdge(6, 9, 8);
  g.addEdge(7, 10, 5);
  g.addEdge(8, 10, 11);
  g.addEdge(8, 11, 11);
  g.addEdge(9, 12, 2);
  g.addEdge(10, 13, 10);
  g.addEdge(10, 15, 10);
  g.addEdge(11, 7, 4);
  g.addEdge(11, 14, 4);
  g.addEdge(12, 14, 12);
  g.addEdge(12, 15, 12);
  g.addEdge(13, 16, 6);
  g.addEdge(14, 13, 2);
  g.addEdge(14, 16, 2);
  g.addEdge(15, 16, 9);
}

/* Implementar um destrutor depois ? */
