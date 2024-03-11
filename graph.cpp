#include "graph_header.hpp"
#include <iostream>
using namespace std;

Graph::Graph(int n, int m)
{
  this->N = n;
  this->M = m;
  time.resize(n);
  successorJob.resize(n);
  successorMachine.resize(n);
  verticeInDegree.resize(n);
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
  addInDegree(b);
}

void Graph::addInDegree(int b)
{
  verticeInDegree[b]++;
}

vector<unsigned> Graph::traverseTopo()
{
  vector<unsigned> result;
  for (int i = 0; i < N; i++)
  {
    if (verticeInDegree[i] == 0)
    {
      if (successorJob[i] != 0)
      {
        verticeInDegree[successorJob[i]]--;
      }
      else if (successorMachine[i] != 0)
      {
        verticeInDegree[successorMachine[i]]--;
      }
      verticeInDegree[i] = -1;
      result.push_back(i);
      i = 0;
    }
  }
  return result;
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

// Essas funções de print são só pra testes, devo remover posteriormente
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

void Graph::printInDegree()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << verticeInDegree[v] << endl;
  }
}

void Graph::printVector(vector<unsigned> &vec)
{
  for (int i = 0; i < vec.size(); ++i)
  {
    cout << vec[i] << " --> ";
  }
  cout << endl;
}

/* Implementar um destrutor depois ? */
