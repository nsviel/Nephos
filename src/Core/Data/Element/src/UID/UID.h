#pragma once

#include <iostream>
#include <unordered_set>
#include <random>
#include <mutex>

namespace dat::gph{class Node;}


namespace dat::elm{

class UID
{
public:
  //Constructor / Destructor
  UID();
  ~UID();

public:
  //Main function
  int generate_UID();

private:
  int generate_rdm_UID();
  bool is_unique(int uid);

private:
  std::unordered_set<int> set_uid;
  std::mt19937 generator;
  std::uniform_int_distribution<int> distribution;
  std::mutex mutex;
};

}
