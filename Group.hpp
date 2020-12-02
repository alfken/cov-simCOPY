#pragma once

struct group_t {
  int n_i{1};        // Infection attempts
  int n_ai{1};       // Infection attempts (asymptomatic)
  float s{1.0f};     // Susceptibility
  float p_i{0.1f};   // Infectiousness
  float p_ai{0.05f}; // Infectiousness (asymptopmatic)
  float p_v{0.9f};   // Vaccine effectiveness
  int d_v{28};       // Vaccine duration
  int d_i{14};       // Infection duration
  int d_ai{14};      // Infection duration (asymptopmatic)  
};
