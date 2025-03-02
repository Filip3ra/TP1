#include <iostream>
#include <vector>
#include <queue>
#include "file_header.hpp"
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

*/

int main(int argc, char *argv[])
{
     /* Caminha topológica no Grafo - item 2.1

          int n = 17;
          int m = 0;
          Graph g(n, m);

          g.initializeJobSuccessors(g);
          g.initializeMachineSuccessors(g);

          vector<unsigned> v = g.traverseTopo();
          g.printVector(v);
     */

     /* Resolução para instâncias - item 2.2 */
     if (argc < 2)
     {
          cout << "Informe o nome do arquivo: ./program [filename]" << endl;
          return 0;
     }
     std::string nome_arquivo = argv[1];

     // Criar uma instância da classe JobShopScheduler
     JobShopScheduler scheduler(nome_arquivo);

     scheduler.printMakes();

     return 0;
}