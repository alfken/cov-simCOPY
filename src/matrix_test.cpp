#include <iostream>
#include "Graph.hpp"
#include "Results.hpp"
#include "Simulator.hpp"
using namespace std;

int main(int argc, char *argv[]) {

  int L = 10;
  int D_zero = 5;
  // // // int t = 50;

  if (argc == 3) {
    L = stoi(argv[1]);
    D_zero = stoi(argv[2]);
    // t = stoi(argv[3]);
  } else if (argc != 1) {
    cout << "Usage: " << argv[0] << " L D0 t\n";
    return 1;
  }





  srand(1);
  // srand(time(NULL));
  Graph g;
  g.matrix_graph(L, D_zero);

  Simulator s;
  // // // settings_t settings;
  // // // settings.t_end = t;

  Results results = s.simulate(g);
  // // // Results results = s.simulate(settings, g);
  results.save_to_file("data.txt");
  results.print(L*L);
  return 0;
}