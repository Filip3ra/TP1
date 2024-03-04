#pragma once
#include <vector>
#include <utility>

using namespace std;

class Graph
{
private:
  int N; // Número de vértices do grafo
  vector<vector<pair<int, int>>> adjList;

public:
  Graph(int n);
  void addEdge(int a, int b, int weight);
  void printGraph();
  void printGraphDegree(const vector<int> &degrees);
  void initializeGraph(Graph &g);
  vector<int> calculateDegree();
};