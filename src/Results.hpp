#pragma once
#include <string>
#include <vector>
#include <iostream>

struct result_t {
  int s{0};
  int a{0};
  int i{0};
  int v{0};
  int r{0};
};

class Results {
private:
  std::vector<result_t> results;
  std::vector<std::vector<result_t>> results_by_region;
public:
  void add_susceptible(int n);
  void add_susceptible();
  void add_asymptomatic(int n);
  void add_asymptomatic();
  void add_infected(int n);
  void add_infected();
  void add_vaccinated(int n);
  void add_vaccinated();
  void add_removed(int n);
  void add_removed();
  void prepare_new_region();
  void prepare_new_result();
  void print(int N);
  void save_to_file(std::string file_name);
  void write_to_output_stream(std::ostream& stream);
  void write_last_to_output_stream(std::ostream& stream);
};
