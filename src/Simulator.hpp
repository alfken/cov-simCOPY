#pragma once
#include <iostream>
#include <memory>
#include "Graph.hpp"
#include "IOStreamHandler.hpp"
#include "Results.hpp"
#include "VaccinationStrategies.hpp"
#include "VaccinationStrategy.hpp"
using namespace std;

class Simulator {
private:
/**
  @initial_infections number of initially infected agents.
  @L                  the square root of the population.
  @days_sick          how long is one person sick.
  @D0                 the square root of the population.
  @T0                 the time step when a lockdown is put forth.
  @t_end              number of time steps the simulation iterates.
  @betaC              probability that Covid-19 transmits when two people meet.
  @random_seed        true if the seed is random, else false.
*/ // Parameters set to their default values:
  int initial_infections = 4;
  int L = 7;
  int days_sick = 14;
  int D0 = 2;
  int T0 = 60;
  int t_end = 60;
  float betaC = 0.25;
  bool random_seed = false;

  // Parameters from the document (except vaccine type)
  bool select_all{true}; // Whether or not agents try to infect all neighbours
  unsigned int T{50};              // Simulation duration
  unsigned int N_init_infected{4}; // Initially infected agents
  // Unused
  unsigned int T_v{10};            // Vaccination start time
  unsigned int n_v{10};            // Vaccines available per timestep

  shared_ptr<VaccinationStrategy> vac_strat;
  
  /**
    Infects n agents at time t=0.
   */
  void infect_initial(Graph& edges, int n);

public:
  Simulator(shared_ptr<VaccinationStrategy>& vs);

  /**
    Performs a single iteration at time t.
   */
  void iterate(Results& results, Graph& edges, int t);

  /**
    Runs a simulation for given settings for the specified graph `edges`.
   */
  Results simulate(Graph& edges, bool print_each_result);
  Results simulate(Graph& edges);

  // Allow the initializer function to access private members
  friend void initialize_simulator_from_stream(istream& stream, Simulator& s);
};
