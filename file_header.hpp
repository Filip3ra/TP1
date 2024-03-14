#pragma once

#include <vector>
#include <string>

class JobShopScheduler
{
public:
  // Construtor
  JobShopScheduler(const std::string &nome_arquivo);

  // Função para imprimir as informações gerais do arquivo de entrada
  void printInfo();
  // Função para imprimir uma matriz
  void printMatrix(const std::vector<std::vector<int>> &matriz);

private:
  // Variáveis para armazenar informações do cabeçalho
  int nb_of_jobs;
  int nb_of_machines;
  int time_seed;
  int machine_seed;
  int upper_bound;
  int lower_bound;

  // Matrizes para armazenar Times e Machines
  std::vector<std::vector<int>> times_matrix;
  std::vector<std::vector<int>> machines_matrix;

  // Função para ler o arquivo e extrair as informações
  void fileReader(const std::string &nome_arquivo);
};
