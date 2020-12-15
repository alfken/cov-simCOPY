#include <vector>
#include <memory>
#include "Agent.hpp"
#include "Graph.hpp"
#include "Results.hpp"

group_t Agent::default_group;

void Agent::try_infecting_neighbour(int t, int target_id, Graph& edges) {
  Agent& n = edges.node_values[target_id];
  if (n.is_susceptible(t)) {
    float roll = (float)rand() / (float)RAND_MAX;
    float risk;
    if (i) {
      risk = group->p_i * n.group->s;
    } else {
      risk = group->p_ai * n.group->s;
    }
    if (roll < risk)
      n.infect(t);
  }
}

Agent::Agent(int id, std::shared_ptr<group_t> group)
  : id(id), group(group) {
  s = true;
  a = false;
  i = false;
  v = false;
  r = false;
  infected_on = -1;
}

Agent::Agent(int id)
  : Agent::Agent(id, std::make_shared<group_t>(default_group)) {}

void Agent::assign_group(std::shared_ptr<group_t>& new_group) {
  group = new_group;
}

bool Agent::is_infected(int t) {
  return (i || a) && t > infected_on;
}

bool Agent::is_susceptible(int t) {
  return s;
}

bool Agent::is_travelling(int t) {
  return group->p_t > (float) rand() / (float) RAND_MAX;
}

void Agent::infect(int t) {
  if (s) {
    s = false;
    float roll = (float)rand() / (float)RAND_MAX;
    if (roll >= group->a_p) {
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

void Agent::try_infecting_n_neighbours(int t, Graph& edges) {
  if (!is_infected(t))
    return;
  std::vector<int> n_ids = edges.neighbours(id);
  int attempts = i ? group->n_i : group->n_ai;
  for (int i = 0; i < attempts; i++) {
    int target = rand() % n_ids.size();
    try_infecting_neighbour(t, n_ids[target], edges);
  }
}

void Agent::try_infecting_on_travel(int t, Graph& edges) {
  int region = edges.get_agent_region(id);
  std::vector<int> candidate_regions = edges.get_neighbouring_regions(region);
  if (candidate_regions.size() > 0) {
    int destination_index = rand() % candidate_regions.size();
    int destination = candidate_regions[destination_index];
    int dst_start = edges.region_agent_offsets[destination];
    int dst_end;
    if (destination == (int) edges.region_agent_offsets.size() - 1)
      dst_end = edges.node_values.size();
    else
      dst_end = edges.region_agent_offsets[destination + 1];
    int n_potential_targets = dst_end - dst_start;
    int n_attempts = i ? group->n_i : group->n_ai;
    for (int i = 0; i < n_attempts; i++) {
      int target_id = rand() % n_potential_targets + dst_start;
      try_infecting_neighbour(t, target_id, edges);
    }
  }
}

void Agent::update_infection(int t) {
  if (i && infected_on + group->d_i < t) {
    i = false;
    r = true;
  } else if (a && infected_on + group->d_ai < t) {
    a = false;
    r = true;
  }
}

void Agent::update_results(int t, Results& results) {
  if (s || ((i || a) && t == infected_on))
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
