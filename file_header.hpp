#pragma once
#include <vector>
#include <string>
#include "graph_header.hpp"
using namespace std;

class JobShopScheduler
{
public:
  // Construtor
  JobShopScheduler(const string &file_name);

  // Função para imprimir as informações gerais do arquivo de entrada
  void printInfo();

  // Imprime limite inferior, makespan obtido e diferença percetual para a instância atual
  void printMakes() const;

  unsigned getMakes() const;

private:
  // Variáveis para armazenar informações do cabeçalho
  int nb_of_jobs;
  int nb_of_machines;
  int time_seed;
  int machine_seed;
  int upper_bound;
  int lower_bound;
  unsigned makespan;

  // Matrizes para armazenar Times e Machines
  vector<vector<int>> times_matrix;
  vector<vector<int>> machines_matrix;

  // Função para ler o arquivo e extrair as informações
  void fileReader(const string &file_name);

  // Função para imprimir uma matriz
  void printMatrix(const vector<vector<int>> &matrix);

  // Gera um dag incompleto baseado nas matrizes de tempos e máquinas
  Graph generateDag() const;

  // Gera as arestas de máquina do dag passado como parametro
  void gifflerThompson(Graph& dag) const;

  // Calcula os tempos de inicio de cada operação e o makespan se baseando no dag passado como parametro
  vector<unsigned> calcStartTimes(Graph& dag, vector<unsigned>& prev, unsigned& lastOp);

  // Recebe o prev e lastOp de uma solução e retorna o caminho critico dessa solução em critic
  void computeCriticPath(vector<unsigned>& critic, vector<unsigned>& prev, unsigned& lastOp);

  // Troca as posições de op1 e op2. Supõe que op1 e op2 estão na mesma máquina e que op2 é sucessora de op1.
  void swap(Graph& dag, unsigned op1, unsigned op2);

  void generateCandidates(vector<pair<unsigned, unsigned>>& candidates, vector<unsigned>& criticPath);

  // Calcula o tempo mínimo restante para terminar o job j logo antes de ser processado na máquina m
  unsigned calcRemainingTime(unsigned j, unsigned m) const;

  // Gera os vetores op_to_mach e op_to_job que armazenam, respectivamente, a máquina e o job de determinada operação x;
  void initAux(vector<unsigned>& op_to_mach, vector<unsigned>& op_to_job) const;
};
