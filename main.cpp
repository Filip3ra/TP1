#include <iostream>
#include <vector>
#include "header.hpp"
#include "graph_header.hpp"

using namespace std;

/* Makespan: reduzir ao máximo o tempo total necessário para
completar todas as tarefas em um ambiente de produção.
O makespan é o tempo total decorrido desde o início até a
conclusão de todas as tarefas em um determinado cronograma de produção.

No problema Job Shop, há um conjunto de trabalhos que precisam ser
processados em diferentes máquinas, com cada trabalho consistindo
em uma sequência específica de operações que devem ser executadas
em ordem específica. Cada operação de um trabalho deve ser processada
em uma máquina particular, e cada máquina só pode processar uma
operação de cada vez.

Parte 1: Implementar um algoritmo de percorrimento topológico para
percorrer o grafo do trabalho.

Parte 2:
*/

int main()
{
  Graph g(5);
  g.initializeGraph(g);
  g.printGraph();
  return 0;
}