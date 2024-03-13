#pragma once

#include <vector>
#include <string>

class JobShopScheduler
{
public:
  // Construtor
  JobShopScheduler(const std::string &nome_arquivo);

  // Função para imprimir as informações
  void imprimir_informacoes();

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
  void ler_arquivo(const std::string &nome_arquivo);

  // Função para imprimir uma matriz
  void imprimir_matriz(const std::vector<std::vector<int>> &matriz);
};
