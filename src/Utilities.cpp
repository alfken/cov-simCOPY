#include <vector>
#include <set>
#include <iostream>
#include <string>
#include "Utilities.hpp"

std::set<int> unique_random_numbers(int n, int max) {
  std::set<int> numbers;
  if (n > max) {
    std::cout << "random_numbers: n cant be larger than total\n";
    return numbers;
  }
  while ((int)numbers.size() < n) {
      numbers.insert(rand() % max);
    }
  return numbers;
}

// https://stackoverflow.com/a/46931770
std::vector<std::string> split (std::string s, std::string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
    token = s.substr (pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back (token);
  }

  res.push_back (s.substr (pos_start));
  return res;
}
