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
  // vector<vector<pair<int, int>>> adjList;

public:
  Graph(int n, int m);
  void SJ_addEdge(int a);
  void SM_addEdge(int a);
  void printGraph();
  void printGraphDegree(const vector<int> &degrees);
  void initializeGraph(Graph &g);
  void initializeJobSuccessors(Graph &g);
  void initializeMachineSuccessors(Graph &g);
  vector<int> calculateDegree();
};