#include "file_header.hpp"
#include <climits>
#include <set>

Graph JobShopScheduler::generateDag() const
{
  Graph g(nb_of_jobs * nb_of_machines + 1, nb_of_jobs * (nb_of_machines - 1));
  unsigned op_index;

  // Adiciona todas as arestas que indicam precendencia dentro dos jobs e os pesos de cada v�rtice
  for (int i = 1; i <= nb_of_jobs; ++i)
  {
    for (int j = 1; j <= nb_of_machines; ++j)
    {
      op_index = (i - 1) * nb_of_machines + j;
      g.setOpTime(op_index, times_matrix[i - 1][j - 1]);
      if (op_index % nb_of_machines)
        g.setOpJobSuccessor(op_index, op_index + 1);
    }
  }

  return g;
}

void JobShopScheduler::initAux(vector<unsigned> &op_to_mach, vector<unsigned> &op_to_job) const
{
  // Dada uma opera��o op do job j, op_to_job[op] = j
  // Dada uma opera��o op da m�quina m, op_to_mach[op] = m

  unsigned op_index;

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

  // Encontra o indice da operação do job j que precisa ser executada na m�quina m
  for (i = 0; i < nb_of_machines; ++i)
  {
    if (machines_matrix[j][i] == m)
    {
      break;
    }
  }

  // Calcula a soma dos tempos de todas as opera��es que s�o processadas ap�s a opera��o i do job j  incluindo i
  for (i; i < nb_of_machines; ++i)
  {
    sum += times_matrix[j][i];
  }

  return sum;
}

void JobShopScheduler::gifflerThompson(Graph &dag) const
{
  set<int> ready;
  vector<unsigned> machine_time(nb_of_machines + 1, 0);
  vector<unsigned> job_time(nb_of_jobs + 1, 0);
  vector<unsigned> op_to_job;
  vector<unsigned> op_to_mach;
  vector<unsigned> mach_leaf(nb_of_machines + 1, 0);
  unsigned counter = 0;

  // Inicializa op_to_mach e op_to_job. op_to_job[i] = j pois a opera��o i pertence ao job j. op_to_mach[i] = m pois a opera��o i ser� executada na m�quina m
  initAux(op_to_mach, op_to_job);

  // Insere em ready a primeira opera��o de cada job
  for (unsigned i = 0; i < nb_of_jobs; ++i)
  {
    ready.insert((i * nb_of_machines) + 1);
  }

  while (!ready.empty())
  {

    ++counter;
    unsigned earl_comp = UINT_MAX;
    unsigned mach = 0;

    // Encontra o menor tempo de termino earl_comp e a m�quina mach associada a ele entre as opera��es de ready
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

    // Insere em ready_0 todas as opera��es em ready que s�o executadas na m�quina mach
    for (unsigned op : ready)
    {
      if (op_to_mach[op] == mach)
      {
        ready_0.push_back(op);
      }
    }

    vector<unsigned> ready_1;

    // Insere em ready_1 todas as opera��es em ready_0 que possuem um tempo de in�cio menor que earl_comp
    for (unsigned op : ready_0)
    {
      unsigned start_time = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]);
      if (start_time < earl_comp)
      {
        ready_1.push_back(op);
      }
    }

    unsigned op = ready_1[0];

    // Seleciona uma opera��o de ready_1 para ser agendada cujo o tempo m�nimo para que o respectivo job termine seja o maior
    for (unsigned i = 1; i < ready_1.size(); ++i)
    {
      if (calcRemainingTime(op_to_job[ready_1[i]] - 1, op_to_mach[ready_1[i]] - 1) > calcRemainingTime(op_to_job[op] - 1, op_to_mach[op] - 1))
      {
        op = ready_1[i];
      }
    }

    // Adiciona uma aresta entre a �ltima opera��o de um m�quina e a nova opera��o que ser� agendada nessa m�quina
    if (mach_leaf[op_to_mach[op]])
    {
      dag.setOpMachineSuccessor(mach_leaf[op_to_mach[op]], op);
    }

    // Atualiza o vetor mach_leaf que armazena o �ltima opera��o agendada em determinada m�quina
    mach_leaf[op_to_mach[op]] = op;

    // Remove a opera��o agendada do vetor de opera��es prontas para serem agendadas
    ready.erase(op);

    // Adiciona o successor da opera��o agendada no vetor ready se ele existir
    if (dag.getJobSuccessor(op))
    {
      ready.insert(dag.getJobSuccessor(op));
    }

    // Atualiza os vetores de tempo das m�quina e jobs com o tempo da opera��o rec�m agendada
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

  // Gera a ordena��o topologica do dag que representa o schedule gerado
  topo_sort = dag.traverseTopo();

  // Percorre a ordena��o topol�gica
  for (unsigned i = 0; i < topo_sort.size(); ++i)
  {
    unsigned op = topo_sort[i];

    // Calcula o tempo de termino da opera��o op
    max = start_times[op] + dag.getOpTime(op);

    // Atualiza o makespan se o tempo de termino de op for maior que o makespan atual
    if (max > makespan)
    {
      makespan = max;
    }

    // Obt�m o sucessor dentro do job da opera��o op
    next_op = dag.getJobSuccessor(op);

    // Atualiza o tempo de in�cio da opera��o sucessora se ela existe e se o tempo de t�rmino de op for maior que o tempo de inicio atual de next_op
    if (next_op && start_times[next_op] < max)
    {
      start_times[next_op] = max;
    }

    // Obt�m o sucessor dentro da m�quina da opera��o op
    next_op = dag.getMachineSuccessor(op);

    // Atualiza o tempo de in�cio da opera��o sucessora se ela existe e se o tempo de t�rmino de op for maior que o tempo de in�cio atual de next_op
    if (next_op && start_times[next_op] < max)
    {
      start_times[next_op] = max;
    }
  }

  return start_times;
}