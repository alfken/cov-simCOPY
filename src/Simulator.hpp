#pragma once
#include "Results.hpp"
#include "Graph.hpp"

// // // struct settings_t {
  // // // int initial_infections{2}; // How many are infected initially
  // // // int days_sick{14}; // How long is one person sick
  // // // int t_end{50}; // How many steps should the simulation iterate
// // // };

class Simulator {
private:
  int initial_infections{2}; // How many are infected initially
  int days_sick{14};         // How long is one person sick
  int t_end{50};             // How many steps should the simulation iterate
  void infect_initial(Graph& edges, int n);
public:
  // /*
    // Carry out a single iteration at time t.
   // */
  // Simulator(Results& result, Graph& edges, settings_t& settings, int t);

  /*
    Carry out a single iteration at time t.
   */
  void iterate(Results& result, Graph& edges, int t);
  // // // void iterate(Results& result, Graph& edges, settings_t& settings, int t);

  /*
    Run a simulation for a given set of settings with some specified graph.
   */
  Results simulate(Graph& edges);
  // // // Results simulate(settings_t& settings, Graph& edges);
};
