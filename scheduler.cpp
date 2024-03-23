#include "file_header.hpp"
#include <climits>
#include <set>

Graph JobShopScheduler::generateDag() const
{
  Graph g(nb_of_jobs * nb_of_machines + 1, nb_of_jobs * (nb_of_machines - 1));
  unsigned op_index;

  for (int i = 1; i <= nb_of_jobs; ++i)
  {

    for (int j = 1; j <= nb_of_machines; ++j)
    {
      op_index = (i - 1) * nb_of_machines + j;
      g.setOpTime(op_index, times_matrix[i - 1][j - 1]);
      if (op_index % nb_of_machines) g.setOpJobSuccessor(op_index, op_index + 1);
    }
  }

  return g;
}

void JobShopScheduler::initAux(vector<unsigned> & op_to_mach, vector<unsigned> & op_to_job) const
{
  unsigned op_index;

  op_to_job.resize(nb_of_jobs * nb_of_machines + 1, 0);
  op_to_mach.resize(nb_of_jobs * nb_of_machines + 1, 0);

  for (unsigned i = 1; i <= nb_of_jobs; ++i)
  {
    for (unsigned j = 1; j <= nb_of_machines; ++j)
    {
      op_index = (i - 1) * nb_of_machines + j;
      op_to_job[op_index] = i;
      op_to_mach[op_index] = machines_matrix[i-1][j-1];
    }
  }
}

unsigned JobShopScheduler::calcRemainingTime(unsigned j, unsigned m) const
{
  unsigned sum = 0;
  unsigned i = 0;
  for (i = 0; i < nb_of_machines; ++i)
  {
    if (machines_matrix[j][i] == m)
    {
      break;
    }
  }

  for (i; i < nb_of_machines; ++i) {
    sum += times_matrix[j][i];
  }

  return sum;

}

void JobShopScheduler::gifflerThompson(Graph & dag) const
{
  set<int> ready;
  vector<unsigned> machine_time(nb_of_machines+1, 0);
  vector<unsigned> job_time(nb_of_jobs+1, 0);
  vector<unsigned> op_to_job;
  vector<unsigned> op_to_mach;
  vector<unsigned> mach_leaf(nb_of_machines+1, 0);
  unsigned counter = 0;


  initAux(op_to_mach, op_to_job);

  for (unsigned i = 0; i < nb_of_jobs; ++i)
  {
    ready.insert((i * nb_of_machines) + 1);
  }

  while (!ready.empty())
  {

    ++counter;
    unsigned earl_comp = UINT_MAX;
    unsigned mach = 0;

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

    for (unsigned op : ready)
    {
      if (op_to_mach[op] == mach)
      {
        ready_0.push_back(op);
      }
    }

    vector<unsigned> ready_1;

    for (unsigned op : ready_0)
    {
      unsigned start_time = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]);
      if (start_time < earl_comp)
      {
        ready_1.push_back(op);
      }
    }

    unsigned op = ready_1[0];
    unsigned auxOp = op;
    for (unsigned i = 1; i < ready_1.size(); ++i)
    {
     /* if (dag.getOpTime(op) > dag.getOpTime(ready_1[i]))
      {
        auxOp = ready_1[i];
      }*/

      if (calcRemainingTime(op_to_job[ready_1[i]]-1, op_to_mach[ready_1[i]]-1) > calcRemainingTime(op_to_job[op]-1, op_to_mach[op]-1))
      {
        auxOp = ready_1[i];
      }

      op = auxOp;
    }

    if (mach_leaf[op_to_mach[op]])
    {
      dag.setOpMachineSuccessor(mach_leaf[op_to_mach[op]], op);
    }

    mach_leaf[op_to_mach[op]] = op;

    ready.erase(op);

    if (dag.getJobSuccessor(op))
    {
      ready.insert(dag.getJobSuccessor(op));
    }

    unsigned earl_start = max(machine_time[op_to_mach[op]], job_time[op_to_job[op]]);
    machine_time[op_to_mach[op]] = earl_start + dag.getOpTime(op);
    job_time[op_to_job[op]] = earl_start + dag.getOpTime(op);
  }
}
