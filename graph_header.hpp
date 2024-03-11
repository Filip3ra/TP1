#pragma once
#include <vector>
#include <utility>

using namespace std;

class Graph
{
private:
  unsigned N;
  unsigned M;
  vector<unsigned> successorJob;
  vector<unsigned> successorMachine;
  vector<unsigned> time;
  vector<unsigned> verticeInDegree;

public:
  Graph(int n, int m);
  void addEdge(vector<unsigned> &vec, int a, int b);
  void addInDegree(int b);
  int getJobSuccessor(int a);
  int getMachineSuccessor(int a);
  void initializeJobSuccessors(Graph &g);
  void initializeMachineSuccessors(Graph &g);
  vector<unsigned> traverseTopo();
  void printSJ();
  void printSM();
  void printInDegree();
  void printVector(vector<unsigned> &vec);
};