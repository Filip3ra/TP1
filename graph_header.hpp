#pragma once
#include <vector>
#include <utility>

using namespace std;

class Graph
{
private:
  unsigned N;
  unsigned M;
  vector<unsigned> successor_job;
  vector<unsigned> successor_machine;
  vector<unsigned> time;
  vector<unsigned> vertice_in_degree;

public:
  Graph();
  Graph(int n, int m);
  void addEdge(vector<unsigned> &vec, int a, int b);
  void addInDegree(int b);
  int getJobSuccessor(int a);
  void setOpJobSuccessor(const unsigned op, const unsigned successor);
  int getMachineSuccessor(int a);
  void setOpMachineSuccessor(const unsigned op, const unsigned successor);
  int getOpTime(const unsigned op);
  void setOpTime(const unsigned op, const unsigned time);
  void initializeJobSuccessors(Graph &g);
  void initializeMachineSuccessors(Graph &g);
  vector<unsigned> traverseTopo();
  void printSJ();
  void printSM();
  void printInDegree();
  void printVector(vector<unsigned> &vec);
};