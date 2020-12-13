#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Agent.hpp"
#include "Group.hpp"

using namespace std;

class Relation {
public:
  int distance;

  Relation(int d);
};

class Graph {
public:
  vector<int> offsets;
  vector<int> edges;
  vector<Relation> edge_values;
  vector<Agent> node_values;

  vector<int> region_agent_offsets;
  vector<int> region_connection_offsets;
  vector<int> region_connections;
  

  /* Read node information from file.
     Format of file should be:
     NODE_ID CONNECTED_TO_1 CONNECTED_TO_2 ...
     on each line of the file
     Example:
     0 1 2 3
     1 0 2
     2 0 1
     3 0
  */
  void input_from_file(string file_name);

  /* Create a graph with dimensions *size*
     with same connection as an matrix with
     distance *distance*.
  */
  void matrix_graph(int size, int distance);

  /*
    Generate a Newman-Watts small world network
    from a 1d lattice with length l, neighbourhood 
    radius k, and shortcut probability p
   */
  void nw_small_world(int l, int k, float p);
  
  /*
    Initializes a default graph with no specific 
    parameters, useful if nothing else has been 
    specified. Implemented as a matrix graph.
   */
  void default_graph();

  /*
    Assign groups to already-existing agents from 
    a vector of available groups, with a uniform 
    distribution.
   */
  void assign_groups(vector<shared_ptr<group_t>>& groups);

  /* Returns list of neighbours of node *id* */
  vector<int> neighbours(int id);

  /* Returns amount of nodes */
  int node_count();

  Agent get_node(int id);


  /* Prints information about the graph */
  void print_graph();

  /* Print a graph that can be read for generation later on */
  void write_generatable_graph(ostream& stream);

  /* Read a graph written with write_generatable_graph() */
  void read_generatable_graph(istream& stream);

  /* Set the connections between regions */
  void set_region_connections_from_stream(istream& stream);
};
