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
}

int Graph::getJobSuccessor(int a)
{
  return successorJob[a];
}

int Graph::getMachineSuccessor(int a)
{
  return successorMachine[a];
}

void Graph::addEdge(vector<unsigned> &vec, int a, int b)
{
  vec[a] = b;
}

void Graph::initializeJobSuccessors(Graph &g)
{
  g.addEdge(successorJob, 7, 10);
  g.addEdge(successorJob, 10, 3);
  g.addEdge(successorJob, 4, 1);
  g.addEdge(successorJob, 1, 2);
  g.addEdge(successorJob, 8, 14);
  g.addEdge(successorJob, 14, 5);
  g.addEdge(successorJob, 11, 15);
  g.addEdge(successorJob, 15, 9);
  g.addEdge(successorJob, 12, 13);
  g.addEdge(successorJob, 13, 6);
}

void Graph::initializeMachineSuccessors(Graph &g)
{
  g.addEdge(successorMachine, 7, 8);
  g.addEdge(successorMachine, 8, 2);
  g.addEdge(successorMachine, 2, 12);
  g.addEdge(successorMachine, 12, 9);
  g.addEdge(successorMachine, 10, 1);
  g.addEdge(successorMachine, 1, 11);
  g.addEdge(successorMachine, 11, 14);
  g.addEdge(successorMachine, 14, 13);
  g.addEdge(successorMachine, 4, 3);
  g.addEdge(successorMachine, 3, 5);
  g.addEdge(successorMachine, 5, 15);
  g.addEdge(successorMachine, 15, 6);
}

void Graph::printSJ()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << successorJob[v] << endl;
  }
}

void Graph::printSM()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << successorMachine[v] << endl;
  }
}
/* Implementar um destrutor depois ? */
