#include "graph_header.hpp"
#include <iostream>
using namespace std;

// Construtor
Graph::Graph(int n, int m)
{
  this->N = n;
  this->M = m;
  time.resize(n);
  successorJob.resize(n);
  successorMachine.resize(n);
  // adjList.resize(n);
}

/*como fazer uma função generica que, independente do vector
passado ele sempre irá adicionar o elementos */
void Graph::SJ_addEdge(int a, int b)
{
  successorJob[a] = b;
}

void Graph::SM_addEdge(int a, int b)
{
  successorMachine[a] = b;
}

void Graph::printGraph(vector<unsigned> &vec)
{

  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << vec[v];
  }
}

void Graph::initializeJobSuccessors(Graph &g)
{
  g.SJ_addEdge(7, 10);
  g.SJ_addEdge(10, 3);
  g.SJ_addEdge(1, 3);
  g.SJ_addEdge(1, 2);
  g.SJ_addEdge(8, 14);
  g.SJ_addEdge(14, 5);
  g.SJ_addEdge(11, 15);
  g.SJ_addEdge(15, 9);
  g.SJ_addEdge(12, 13);
  g.SJ_addEdge(13, 6);
}

void Graph::initializeMachineSuccessors(Graph &g)
{
}

void Graph::initializeGraph(Graph &g)
{
}

/* Implementar um destrutor depois ? */
