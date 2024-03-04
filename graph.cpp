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

void Graph::printGraphDegree(const vector<int> &degrees)
{
  for (int v = 0; v < degrees.size(); ++v)
  {
    cout << "Grau do vertice " << v << ": " << degrees[v] << endl;
  }
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

void Graph::initializeJobSuccessors(Graph &g)
{
}

void Graph::initializeMachineSuccessors(Graph &g)
{
}

void Graph::initializeGraph(Graph &g)
{
  g.addEdge(1, 11, 0);
  g.addEdge(1, 2, 0);
  g.addEdge(2, 12, 0);
  g.addEdge(3, 5, 0);
  g.addEdge(4, 3, 0);
  g.addEdge(4, 1, 0);
  g.addEdge(5, 15, 0);
  g.addEdge(7, 8, 0);
  g.addEdge(7, 10, 0);
  g.addEdge(8, 14, 0);
  g.addEdge(8, 2, 0);
  g.addEdge(10, 3, 0);
  g.addEdge(10, 1, 0);
  g.addEdge(11, 15, 0);
  g.addEdge(11, 14, 0);
  g.addEdge(12, 13, 0);
  g.addEdge(12, 9, 0);
  g.addEdge(13, 6, 0);
  g.addEdge(14, 13, 0);
  g.addEdge(14, 5, 0);
  g.addEdge(15, 6, 0);
  g.addEdge(15, 9, 0);
}

/* Implementar um destrutor depois ? */
