#pragma once

class Graph;
#include "Results.hpp"
#include "Group.hpp"

class Agent {
private:
  int id;
  bool s;
  bool a;
  bool i;
  bool v;
  bool r;
  int infected_on;
  const group_t &group;
  static const group_t default_group;

  void try_infecting_neighbour(int t, int id, Graph& edges);

public:
  Agent(int id, const group_t& group);
  Agent(int id);
  
  /*
    Check if the individual can infect people at time t.
  */
  bool is_infected(int t);

  /*
    Check if the individual can still be infected at time t.
  */
  bool is_susceptible(int t);

  /*
    Infect the individual at time t.
  */
  void infect(int t);

  /*
    Make the individual try to infect all of its neighbours at time t.
  */
  void try_infecting_neighbours(int t, Graph& edges);

  /*
    Update the individuals infection, given that an infection last for d time steps.
  */
  void update_infection(int t);
  
  /*
    Update the results with the individual.
  */
  void update_results(int t, Results& results);
};
