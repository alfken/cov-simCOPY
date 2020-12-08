#include <vector>
#include <iostream>
#include "Group.hpp"
#include "Simulator.hpp"
#include "../include/json.hpp"

using namespace std;
using json = nlohmann::json;


void get_groups_from_stream(istream& stream, vector<group_t>& groups) {
  json s;
  stream >> s;

  if (s["groups"].is_array()) {
    for (auto group : s["groups"]) {
      group_t g;
      if (s["n_i"].is_number())
	g.n_i = s["n_i"];
      if (s["n_ai"].is_number())
	g.n_ai = s["n_ai"];
      if (s["s"].is_number())
	g.s = s["s"];
      if (s["p_i"].is_number())
	g.p_i = s["p_i"];
      if (s["p_ai"].is_number())
	g.p_ai = s["p_ai"];
      if (s["p_v"].is_number())
	g.p_v = s["p_v"];
      if (s["d_v"].is_number())
	g.d_v = s["d_v"];
      if (s["d_i"].is_number())
	g.d_i = s["d_i"];
      if (s["d_ai"].is_number())
	g.d_ai = s["d_ai"];
      if (s["a_p"].is_number())
	g.a_p = s["a_p"];
      groups.push_back(g);
    }
  }
}

void initialize_simulator_from_stream(istream& stream, Simulator& sim) {
  json s;
  stream >> s;

  if (s["T"].is_number())
    sim.T = s["T"];
  if (s["N"].is_number())
    sim.N = s["N"];
  if (s["T_v"].is_number())
    sim.T_v = s["T_v"];
  if (s["n_v"].is_number())
    sim.n_v = s["n_v"];
}

void reset_stream(istream& stream) {
  stream.clear();
  stream.seekg(0, stream.beg);
}
