#include "VaccinationStrategies.hpp"
#include "Graph.hpp"
#include <vector>
#include <set>
#include <algorithm>
#include "Utilities.hpp"
#include <iostream>

void RandomStrategy::vaccinate(Graph& g) {

  vector<int> unvaccinated;

  for (int i = 0; i < g.node_count(); ++i) {
    if (!(g.get_node(i).is_vaccinated())) {
      unvaccinated.push_back(i);
    }
  }
  
  if(unvaccinated.size() == 0) return;

  int unvaccinated_count = unvaccinated.size();
  int vaccines = std::min(vaccines_per_day, unvaccinated_count);
  
  set<int> nums = unique_random_numbers(vaccines,
                                        unvaccinated.size());
  for (int i : nums) {
    g.node_values[i].vaccinate();
  }
  
  return;
}

void NothingStrategy::vaccinate(Graph& g) {
  return;
}
