#include "file_header.hpp"
#include <climits>
#include <set>

// teste com cout
#include <iostream>
using namespace std;

Graph JobShopScheduler::generateDag() const
{
  // Define número de vértices e arestas do grafo
  Graph g(nb_of_jobs * nb_of_machines + 1, nb_of_jobs * (nb_of_machines - 1));
  unsigned op_index;

  // Adiciona todas as arestas que indicam precendencia dentro dos jobs e os pesos de cada vértice
  for (int i = 1; i <= nb_of_jobs; ++i)
  {
    for (int j = 1; j <= nb_of_machines; ++j)
    {
      op_index = (i - 1) * nb_of_machines + j;           // índice da operação atual, passa por todas as posições da matriz, 1 - 225
      g.setOpTime(op_index, times_matrix[i - 1][j - 1]); // atribui tempo de processamento atual da op ao vértice
      if (op_index % nb_of_machines)                     // nb_machines é sempre 15, então resto é 0 só quando chega na última op
        g.setOpJobSuccessor(op_index, op_index + 1);     // seta o sucessor de job
    }
  }

  return g;
}

void JobShopScheduler::initAux(vector<unsigned> &op_to_mach, vector<unsigned> &op_to_job) const
{
  // Dada uma operação op do job j, op_to_job[op] = j
  // Dada uma operação op da máquina m, op_to_mach[op] = m

  /* Associa uma operação com sua devida máquina, ou seja,
   o indice 1 pega o primeiro valor da matriz de máquina,
   por exemplo, se for 13, então a op 1 é executada na m13,
   e se op 1 ta associada a primeira posição da matriz time,
   então o valor da primiera posição dessa matriz é o tempo
   de processamento da operação em questão. */

  unsigned op_index;

  // precisa do resize pois recebe sem ter dimensionado o tamanho
  op_to_job.resize(nb_of_jobs * nb_of_machines + 1, 0);
  op_to_mach.resize(nb_of_jobs * nb_of_machines + 1, 0);

  for (unsigned i = 1; i <= nb_of_jobs; ++i)
  {
    for (unsigned j = 1; j <= nb_of_machines; ++j)
    {
      op_index = (i - 1) * nb_of_machines + j;
      op_to_job[op_index] = i;
      op_to_mach[op_index] = machines_matrix[i - 1][j - 1];
    }
  }
}

unsigned JobShopScheduler::calcRemainingTime(unsigned j, unsigned m) const
{
  unsigned sum = 0;
  unsigned i = 0;

  // Encontra o indice da operação do job j que precisa ser executada na máquina m
  for (i = 0; i < nb_of_machines; ++i)
  {
    if (machines_matrix[j][i] == m)
    {
      break;
    }
  }

  // Calcula a soma dos tempos de todas as operações que são processadas após a operação i do job j  incluindo i
  for (i; i < nb_of_machines; ++i)
  {
    sum += times_matrix[j][i];
  }

  return sum;
}

void JobShopScheduler::gifflerThompson(Graph &dag) const
{
  set<int> ready;                                       // op pronta pra execução
  vector<unsigned> machine_time(nb_of_machines + 1, 0); // tempo de maquina
  vector<unsigned> job_time(nb_of_jobs + 1, 0);         // tempo do job
  vector<unsigned> op_to_job;                           // mapeamento de op para job
  vector<unsigned> op_to_mach;                          // mapeamento de op para maquina
  vector<unsigned> mach_leaf(nb_of_machines + 1, 0);    // ultima op agendada em cada maquina
  unsigned counter = 0;

  // Inicializa op_to_mach e op_to_job.
  // op_to_job[i] = j pois a operaçao i pertence ao job j.
  // op_to_mach[i] = m pois a operção i será executada na máquina m
  initAux(op_to_mach, op_to_job);

  // Insere em ready a primeira operaçao de cada job
  // A primeira op, primeiro valor de cada linha coluna 1 da matriz,
  // está sempre pronta, não tem op precedente a elas.
  for (unsigned i = 0; i < nb_of_jobs; ++i)
  {
    ready.insert((i * nb_of_machines) + 1);
  }

  while (!ready.empty())
  {

    ++counter;
    unsigned earl_comp = UINT_MAX;
    unsigned mach = 0;

    // Encontra o menor tempo de termino earl_comp e a máquina mach associada a ele entre as operações de ready
    for (unsigned op : ready)
    {
      unsigned completionTime = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]) + dag.getOpTime(op);
      if (completionTime < earl_comp)
      {
        earl_comp = completionTime;
        mach = op_to_mach[op];
      }
    }

    vector<unsigned> ready_0;

    // Insere em ready_0 todas as operaçães em ready que são executadas na máquina mach
    for (unsigned op : ready)
    {
      if (op_to_mach[op] == mach)
      {
        ready_0.push_back(op);
      }
    }

    vector<unsigned> ready_1;

    // Insere em ready_1 todas as operações em ready_0 que possuem um tempo de início menor que earl_comp
    for (unsigned op : ready_0)
    {
      unsigned start_time = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]);
      if (start_time < earl_comp)
      {
        ready_1.push_back(op);
      }
    }

    unsigned op = ready_1[0];

    // Seleciona uma operação de ready_1 para ser agendada cujo o tempo mínimo para que o respectivo job termine seja o maior
    for (unsigned i = 1; i < ready_1.size(); ++i)
    {
      if (calcRemainingTime(op_to_job[ready_1[i]] - 1, op_to_mach[ready_1[i]] - 1) > calcRemainingTime(op_to_job[op] - 1, op_to_mach[op] - 1))
      {
        op = ready_1[i];
      }
    }

    // Adiciona uma aresta entre a última operação de um máquina e a nova operação que será agendada nessa máquina
    if (mach_leaf[op_to_mach[op]])
    {
      dag.setOpMachineSuccessor(mach_leaf[op_to_mach[op]], op);
    }

    // Atualiza o vetor mach_leaf que armazena o última operação agendada em determinada máquina
    mach_leaf[op_to_mach[op]] = op;

    // Remove a operação agendada do vetor de operações prontas para serem agendadas
    ready.erase(op);

    // Adiciona o successor da operação agendada no vetor ready se ele existir
    if (dag.getJobSuccessor(op))
    {
      ready.insert(dag.getJobSuccessor(op));
    }

    // Atualiza os vetores de tempo das máquina e jobs com o tempo da operação recém agendada
    unsigned earl_start = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]);
    machine_time[op_to_mach[op]] = earl_start + dag.getOpTime(op);
    job_time[op_to_job[op]] = earl_start + dag.getOpTime(op);
  }
}

vector<unsigned> JobShopScheduler::calcStartTimes(Graph &dag)
{
  vector<unsigned> op_to_job;
  vector<unsigned> op_to_mach;
  vector<unsigned> topo_sort;
  vector<unsigned> start_times(nb_of_jobs * nb_of_machines + 1, 0);
  unsigned max = 0;
  unsigned next_op;

  makespan = 0;

  initAux(op_to_mach, op_to_job);

  // Gera a ordenação topologica do dag que representa o schedule gerado
  topo_sort = dag.traverseTopo();

  // Percorre a ordenação topológica
  for (unsigned i = 0; i < topo_sort.size(); ++i)
  {
    unsigned op = topo_sort[i];

    // Calcula o tempo de termino da operação op
    max = start_times[op] + dag.getOpTime(op);

    // Atualiza o makespan se o tempo de termino de op for maior que o makespan atual
    if (max > makespan)
    {
      makespan = max;
    }

    // Obtém o sucessor dentro do job da operação op
    next_op = dag.getJobSuccessor(op);

    // Atualiza o tempo de início da operação sucessora se ela existe e se o tempo de término de op for maior que o tempo de inicio atual de next_op
    if (next_op && start_times[next_op] < max)
    {
      start_times[next_op] = max;
    }

    // Obtém o sucessor dentro da máquina da operação op
    next_op = dag.getMachineSuccessor(op);

    // Atualiza o tempo de início da operação sucessora se ela existe e se o tempo de término de op for maior que o tempo de início atual de next_op
    if (next_op && start_times[next_op] < max)
    {
      start_times[next_op] = max;
    }
  }

  return start_times;
}