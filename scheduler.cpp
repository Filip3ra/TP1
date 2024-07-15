#include "file_header.hpp"
#include <climits>
#include <set>
#include <algorithm>
#include <cassert>

// testes com cout
#include <iostream>
using namespace std;

#define LIST_SIZE 100

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
      op_index = (i - 1) * nb_of_machines + j;           // Índice da operação atual, passa por todas as posições da matriz, 1 - 225
      g.setOpTime(op_index, times_matrix[i - 1][j - 1]); // Atribui tempo de processamento atual da operação ao vértice.
      if (op_index % nb_of_machines)                     // nb_machines é sempre 15, então resto é 0 só quando chega na última op...
        g.setOpJobSuccessor(op_index, op_index + 1);     // ...que seta o sucessor de job
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

  // Encontra o indice da operação do job j
  // que precisa ser executada na máquina m
  for (i = 0; i < nb_of_machines; ++i)
  {
    if (machines_matrix[j][i] == m)
    {
      break;
    }
  }

  // Calcula a soma dos tempos de todas as operações
  // que são processadas após a operação i do job j  incluindo i
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

    // Encontra o menor tempo de termino earl_comp e a
    // máquina mach associada a ele entre as operações de ready
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

    // Insere em ready_0 todas as operaçães em ready que são
    // executadas na máquina mach
    for (unsigned op : ready)
    {
      if (op_to_mach[op] == mach)
      {
        ready_0.push_back(op);
      }
    }

    vector<unsigned> ready_1;

    // Insere em ready_1 todas as operações em ready_0
    // que possuem um tempo de início menor que earl_comp
    for (unsigned op : ready_0)
    {
      unsigned start_time = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]);
      if (start_time < earl_comp)
      {
        ready_1.push_back(op);
      }
    }

    unsigned op = ready_1[0];

    // Seleciona uma operação de ready_1 para ser agendada
    // cujo o tempo mínimo para que o respectivo job termine seja o maior
    for (unsigned i = 1; i < ready_1.size(); ++i)
    {
      if (calcRemainingTime(op_to_job[ready_1[i]] - 1, op_to_mach[ready_1[i]] - 1) > calcRemainingTime(op_to_job[op] - 1, op_to_mach[op] - 1))
      {
        op = ready_1[i];
      }
    }

    // Adiciona uma aresta entre a última operação de
    // uma máquina e a nova operação que será agendada nessa máquina
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

  for (unsigned i = 0; i < (nb_of_jobs * nb_of_machines + 1); ++i)
  {
    if (dag.getMachineSuccessor(i))
      dag.setOpMachinePrev(dag.getMachineSuccessor(i), i);
  }
}

vector<unsigned> JobShopScheduler::calcStartTimes(Graph &dag, vector<unsigned>& prev, unsigned & lastOp)
{
  vector<unsigned> op_to_job;
  vector<unsigned> op_to_mach;
  vector<unsigned> topo_sort;
  vector<unsigned> start_times(nb_of_jobs * nb_of_machines + 1, 0);
  unsigned max = 0;
  unsigned next_op;

  makespan = 0;

  initAux(op_to_mach, op_to_job);
  prev.resize(nb_of_jobs * nb_of_machines + 1);
  fill(prev.begin(), prev.end(), 0);
  lastOp = 0;

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
      lastOp = op;
    }

    // Obtém o sucessor dentro do job da operação op
    next_op = dag.getJobSuccessor(op);

    // Atualiza o tempo de início da operação sucessora se ela existe e se o tempo de término de op for maior que o tempo de inicio atual de next_op
    if (next_op && start_times[next_op] < max)
    {
      start_times[next_op] = max;
      prev[next_op] = op;
    }

    // Obtém o sucessor dentro da máquina da operação op
    next_op = dag.getMachineSuccessor(op);

    // Atualiza o tempo de início da operação sucessora se ela existe e se o tempo de término de op for maior que o tempo de início atual de next_op
    if (next_op && start_times[next_op] < max)
    {
      start_times[next_op] = max;
      prev[next_op] = op;
    }
  }

  return start_times;
}

void JobShopScheduler::computeCriticPath(vector<unsigned>& critic, vector<unsigned>& prev, unsigned& lastOp) {

  critic.clear();

  while (lastOp) {
    critic.push_back(lastOp);
    lastOp = prev[lastOp];
  }

  reverse(critic.begin(), critic.end());
}

void JobShopScheduler::swap(Graph& dag, unsigned op1, unsigned op2) {

  unsigned prevOp1 = dag.getMachinePrev(op1);
  unsigned nextOp2 = dag.getMachineSuccessor(op2);

  if (prevOp1)
  {
    dag.setOpMachineSuccessor(prevOp1, op2);
  }
  dag.setOpMachineSuccessor(op2, op1);
  dag.setOpMachineSuccessor(op1, nextOp2);

  if(nextOp2)
  {
    dag.setOpMachinePrev(nextOp2, op1);
  }
  dag.setOpMachinePrev(op1, op2);
  dag.setOpMachinePrev(op2, prevOp1);
}

void JobShopScheduler::generateCandidates(vector<pair<unsigned, unsigned>>& candidates, vector<unsigned>& criticPath) {

  vector<unsigned> op_to_job;                           // mapeamento de op para job
  vector<unsigned> op_to_mach;                          // mapeamento de op para maquina

  initAux(op_to_mach, op_to_job);
  candidates.clear();

  for (unsigned i = 0; i < criticPath.size()-1; ++i) {
    if (op_to_mach[criticPath[i]] == op_to_mach[criticPath[i + 1]]) {
      candidates.push_back(pair<unsigned, unsigned>(criticPath[i], criticPath[i + 1]));
    }
  }
}

void JobShopScheduler::swapResult(vector<Result>& resultsList, unsigned a, unsigned b) {
  Result aux = resultsList[a];
  resultsList[a] = resultsList[b];
  resultsList[b] = aux;
}

void JobShopScheduler::fillResultsList(Graph& dag, vector<Result>& resultsList, unsigned& resultsListSize, vector<pair<unsigned, unsigned>>& candidates, vector<unsigned>& prev, unsigned& lastOp) {

  unsigned op1;
  unsigned op2;
  bool alreayExists;

  for (unsigned i = 0; i < candidates.size(); ++i) {

    op1 = candidates[i].first;
    op2 = candidates[i].second;

    swap(dag, op1, op2);

    calcStartTimes(dag, prev, lastOp);

    alreayExists = false;
    for (unsigned j = 0; j < resultsListSize; ++j) {
      if (makespan == resultsList[j].makespan) {
        alreayExists = true;
        break;
      }
    }

    if (resultsListSize < LIST_SIZE && !alreayExists) {
      resultsList[resultsListSize] = Result{ makespan, dag, false };
      resultsListSize++;
    }else if(!alreayExists) {
      if (makespan < resultsList[resultsListSize - 1].makespan) {
        resultsList[resultsListSize-1] = Result{ makespan, dag, false };
      }
    }

    unsigned j = resultsListSize - 1;
    while (j > 0 && resultsList[j].makespan < resultsList[j - 1].makespan) {
      swapResult(resultsList, j, j - 1);
      --j;
    }

    swap(dag, op2, op1);
  }
}

void JobShopScheduler::localSearch(Graph& dag) {

  vector<unsigned> prev;
  vector<unsigned> criticPath;
  vector<pair<unsigned, unsigned>> candidates;
  vector<Result> localSearchList(LIST_SIZE);
  unsigned localSearchListSize=0;
  unsigned lastOp;

  for (unsigned i = 0; i < localSearchList.size(); ++i) {
    localSearchList[i].makespan = UINT32_MAX;
  }

  Graph theDag;
  unsigned theMakes;

  calcStartTimes(dag, prev, lastOp);
  theMakes = makespan;
  theDag = dag;
  localSearchList[0] = Result{ theMakes, theDag, false };
  localSearchListSize++;

  while (true) {
    bool finishExec = false;
    for (unsigned i = 0; i < localSearchListSize; ++i) {
      if (!localSearchList[i].expanded) {
        dag = localSearchList[i].dag;
        localSearchList[i].expanded = true;
        finishExec = true;
        break;
      }
    }

    if (!finishExec) break;

    calcStartTimes(dag, prev, lastOp);

    computeCriticPath(criticPath, prev, lastOp);

    generateCandidates(candidates, criticPath);

    //neighbourhoodSearch(dag, candidates, theMakes, prev, lastOp);
    fillResultsList(dag, localSearchList, localSearchListSize, candidates, prev, lastOp);
  }

  dag = localSearchList[0].dag;

  calcStartTimes(dag, prev, lastOp);
}

unsigned JobShopScheduler::getMakes() const {
  return makespan;
}

void JobShopScheduler::setTimeSpent(double milliseconds) {
  millisecondsSpent = milliseconds;
}