#pragma once
#include "Results.hpp"
#include "Graph.hpp"

struct settings_t {
  int t_end{50}; // How many steps should the simulation iterate
  int d{14}; // How long is one person sick
  int initial_infections{1}; // How many are infected initially
};

class Simulator {
private:
  void infect_initial(Graph& edges, int n);
public:
  /*
    Carry out a single iteration at time t.
   */
  void iterate(Results& result, Graph& edges, settings_t& settings, int t);

  /*
    Run a simulation for a given set of settings with some specified graph.
   */
  Results simulate(settings_t& settings, Graph& edges);
};