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
void Graph::SJ_addEdge(int a)
{
  successorJob.push_back(a);
}

void Graph::SM_addEdge(int a)
{
  successorMachine.push_back(a);
}

void Graph::printGraph()
{
  /*
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "]";
    for (auto x : adjList[v]) // "auto" Escolhe automaticamente o tipo de x
      cout << " --> {" << x.first << "," << x.second << "}";
    cout << endl;
  }
  */
}

void Graph::initializeJobSuccessors(Graph &g)
{
}

void Graph::initializeMachineSuccessors(Graph &g)
{
}

void Graph::initializeGraph(Graph &g)
{
}

/* Implementar um destrutor depois ? */
