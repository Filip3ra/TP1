#pragma once
#include <vector>
#include <string>
using namespace std;

class JobShopScheduler
{
public:
  // Construtor
  JobShopScheduler(const string &file_name);

  // Função para imprimir as informações gerais do arquivo de entrada
  void printInfo();
  // Função para imprimir uma matriz
  void printMatrix(const vector<vector<int>> &matrix);

private:
  // Variáveis para armazenar informações do cabeçalho
  int nb_of_jobs;
  int nb_of_machines;
  int time_seed;
  int machine_seed;
  int upper_bound;
  int lower_bound;

  // Matrizes para armazenar Times e Machines
  vector<vector<int>> times_matrix;
  vector<vector<int>> machines_matrix;

  // Função para ler o arquivo e extrair as informações
  void fileReader(const string &file_name);
};
