#include "header.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Construtor
JobShopScheduler::JobShopScheduler(const std::string &nome_arquivo)
{
  ler_arquivo(nome_arquivo);
}

// Função para ler o arquivo e extrair as informações
void JobShopScheduler::ler_arquivo(const std::string &nome_arquivo)
{
  // Abrir o arquivo
  std::ifstream arquivo(nome_arquivo);

  // Verificar se o arquivo foi aberto corretamente
  if (arquivo.is_open())
  {
    std::string linha;

    // Ler as linhas do arquivo
    for (int i = 0; getline(arquivo, linha); ++i)
    {
      std::stringstream ss(linha);
      if (i == 1)
      {
        // Processar informações do cabeçalho
        ss >> nb_of_jobs >> nb_of_machines >> time_seed >> machine_seed >> upper_bound >> lower_bound;
      }
      else if (i >= 3 && i < 18)
      {
        // Processar a matriz Times
        std::vector<int> temp;
        int valor;
        while (ss >> valor)
        {
          temp.push_back(valor);
        }
        times_matrix.push_back(temp);
      }
      else if (i >= 19 && i < 35)
      {
        // Processar a matriz Machines
        std::vector<int> temp;
        int valor;
        while (ss >> valor)
        {
          temp.push_back(valor);
        }
        machines_matrix.push_back(temp);
      }
    }

    // Fechar o arquivo
    arquivo.close();
  }
  else
  {
    // Exibir mensagem de erro se não foi possível abrir o arquivo
    std::cout << "Erro ao abrir o arquivo." << std::endl;
  }
}

// Função para imprimir uma matriz
void JobShopScheduler::imprimir_matriz(const std::vector<std::vector<int>> &matriz)
{
  for (const auto &linha : matriz)
  {
    for (int valor : linha)
    {
      std::cout << valor << " ";
    }
    std::cout << std::endl;
  }
}

// Função para imprimir as informações
void JobShopScheduler::imprimir_informacoes()
{
  // Exibir as informações
  std::cout << "Nb of jobs: " << nb_of_jobs << std::endl;
  std::cout << "Nb of Machines: " << nb_of_machines << std::endl;
  std::cout << "Time seed: " << time_seed << std::endl;
  std::cout << "Machine seed: " << machine_seed << std::endl;
  std::cout << "Upper bound: " << upper_bound << std::endl;
  std::cout << "Lower bound: " << lower_bound << std::endl;

  std::cout << "Times Matrix:" << std::endl;
  imprimir_matriz(times_matrix);

  std::cout << "Machines Matrix:" << std::endl;
  imprimir_matriz(machines_matrix);
}
