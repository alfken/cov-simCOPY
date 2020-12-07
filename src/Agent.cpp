#include <iterator>
#include <vector>
#include "Agent.hpp"
#include "Graph.hpp"
#include "Results.hpp"

const group_t Agent::default_group;

void Agent::try_infecting_neighbour(int t, int target_id, Graph& edges) {
  Agent& n = edges.node_values[target_id];
  if (n.is_susceptible(t)) {
    float roll = (float)rand() / (float)RAND_MAX;
    float risk;
    if (i) {
      risk = group.p_i * n.group.s;
    } else {
      risk = group.p_ai * n.group.s;
    }
    if (roll < risk)
      n.infect(t);
  }
}

Agent::Agent(int id, const group_t& group)
  : id(id), group(group) {
  s = true;
  a = false;
  i = false;
  v = false;
  r = false;
  infected_on = -1;
}

Agent::Agent(int id)
  : Agent::Agent(id, Agent::default_group) {}

bool Agent::is_infected(int t) {
  return (i || a) && t > infected_on;
}

bool Agent::is_susceptible(int t) {
  return s;
}

void Agent::infect(int t) {
  if (s) {
    s = false;
    float roll = (float)rand() / (float)RAND_MAX;
    if (roll >= group.a_p) {
      i = true;
    } else {
      a = true;
    }
    infected_on = t;
  }
}

void Agent::try_infecting_neighbours(int t, Graph& edges) {
  if (!is_infected(t))
    return;
  std::vector<int> n_ids = edges.neighbours(id);
  for (auto n_id : n_ids)
    try_infecting_neighbour(t, n_id, edges);
}

void Agent::update_infection(int t) {
  if (i && infected_on + group.d_i < t) {
    i = false;
    r = true;
  } else if (a && infected_on + group.d_ai < t) {
    a = false;
    r = true;
  }
}

void Agent::update_results(int t, Results& results) {
  if (s || (i && t == infected_on))
    results.add_susceptible();
  else if (a)
    results.add_asymptomatic();
  else if (i)
    results.add_infected();
  else if (v)
    results.add_vaccinated();
  else if (r)
    results.add_removed();
}
