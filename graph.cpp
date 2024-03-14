#include "graph_header.hpp"
#include <iostream>
using namespace std;

Graph::Graph(int n, int m)
{
  this->N = n;
  this->M = m;
  time.resize(n);
  successor_job.resize(n);
  successor_machine.resize(n);
  vertice_in_degree.resize(n);
}

int Graph::getJobSuccessor(int a)
{
  return successor_job[a];
}

int Graph::getMachineSuccessor(int a)
{
  return successor_machine[a];
}

void Graph::addEdge(vector<unsigned> &vec, int a, int b)
{
  vec[a] = b;
  addInDegree(b);
}

void Graph::addInDegree(int b)
{
  vertice_in_degree[b]++;
}

vector<unsigned> Graph::traverseTopo()
{
  vector<unsigned> result;
  for (int i = 1; i < N; i++)
  {
    if (vertice_in_degree[i] == 0)
    {
      if (successor_job[i] != 0)
      {
        vertice_in_degree[successor_job[i]]--;
      }
      if (successor_machine[i] != 0)
      {
        vertice_in_degree[successor_machine[i]]--;
      }
      vertice_in_degree[i] = -1;

      result.push_back(i);
      i = 0;
    }
  }
  return result;
}

void Graph::initializeJobSuccessors(Graph &g)
{
  g.addEdge(successor_job, 7, 10);
  g.addEdge(successor_job, 10, 3);
  g.addEdge(successor_job, 4, 1);
  g.addEdge(successor_job, 1, 2);
  g.addEdge(successor_job, 8, 14);
  g.addEdge(successor_job, 14, 5);
  g.addEdge(successor_job, 11, 15);
  g.addEdge(successor_job, 15, 9);
  g.addEdge(successor_job, 12, 13);
  g.addEdge(successor_job, 13, 6);
}

void Graph::initializeMachineSuccessors(Graph &g)
{
  g.addEdge(successor_machine, 7, 8);
  g.addEdge(successor_machine, 8, 2);
  g.addEdge(successor_machine, 2, 12);
  g.addEdge(successor_machine, 12, 9);
  g.addEdge(successor_machine, 10, 1);
  g.addEdge(successor_machine, 1, 11);
  g.addEdge(successor_machine, 11, 14);
  g.addEdge(successor_machine, 14, 13);
  g.addEdge(successor_machine, 4, 3);
  g.addEdge(successor_machine, 3, 5);
  g.addEdge(successor_machine, 5, 15);
  g.addEdge(successor_machine, 15, 6);
}

// Essas funções de print são só pra testes, devo remover posteriormente
void Graph::printSJ()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << successor_job[v] << endl;
  }
}

void Graph::printSM()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << successor_machine[v] << endl;
  }
}

void Graph::printInDegree()
{
  for (int v = 0; v < N; ++v)
  {
    cout << "[" << v << "] --> " << vertice_in_degree[v] << endl;
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
