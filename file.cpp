#include "file_header.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

// Construtor
JobShopScheduler::JobShopScheduler(const string &file_name)
{
  Graph dag;

  fileReader(file_name);

  high_resolution_clock::time_point startTime = high_resolution_clock::now();

  dag = generateDag();

  gifflerThompson(dag);

  localSearch(dag);

  setTimeSpent(duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count());

}

// Função para ler o arquivo e extrair as informações
void JobShopScheduler::fileReader(const string &file_name)
{
  // Abrir o arquivo
  ifstream file(file_name);


  // Verificar se o arquivo foi aberto corretamente
  if (file.is_open())
  {
    string line;

    // Ler as linhas do arquivo
    for (int i = 0; getline(file, line); ++i)
    {
      stringstream ss(line);
      if (i == 1)
      {
        // Processar informações do cabeçalho
        ss >> nb_of_jobs >> nb_of_machines >> time_seed >> machine_seed >> upper_bound >> lower_bound;
      }
      else if (i >= 3 && i < nb_of_jobs+3) // linha 3 do arquivo
      {
        // Processa matriz Times
        vector<int> temp;
        int value;
        while (ss >> value)
        {
          temp.push_back(value);
        }
        times_matrix.push_back(temp);
      }
      else if (i >= nb_of_jobs + 4 && i < (2*nb_of_jobs+5)) // linha 19 do arquivo
      {
        // Processa matriz Machines
        vector<int> temp;
        int value;
        while (ss >> value)
        {
          temp.push_back(value);
        }
        machines_matrix.push_back(temp);
      }
    }

    file.close();
  }
  else
  {
    // Exibir mensagem de erro se não foi possível abrir o arquivo
    cout << "Erro ao abrir o arquivo." << endl;
  }
}

// Função para imprimir uma matriz
void JobShopScheduler::printMatrix(const vector<vector<int>> &matrix)
{
  for (const auto &line : matrix)
  {
    for (int value : line)
    {
      cout << value << " ";
    }
    cout << endl;
  }
}

// Função para imprimir as informações gerais e as matrizes
void JobShopScheduler::printInfo()
{
  cout << "Nb of jobs: " << nb_of_jobs << endl;
  cout << "Nb of Machines: " << nb_of_machines << endl;
  cout << "Time seed: " << time_seed << endl;
  cout << "Machine seed: " << machine_seed << endl;
  cout << "Upper bound: " << upper_bound << endl;
  cout << "Lower bound: " << lower_bound << endl;

  cout << "Times Matrix:" << endl;
  printMatrix(times_matrix);

  cout << "Machines Matrix:" << endl;
  printMatrix(machines_matrix);
}

// Imprime limite inferior, makespan obtido e diferença percetual para a instância atual
void JobShopScheduler::printMakes() const
{
  cout << lower_bound << " " << makespan << " " << (((double)makespan - (double)lower_bound) / (double)lower_bound) * 100 << " " << millisecondsSpent << endl;
}
