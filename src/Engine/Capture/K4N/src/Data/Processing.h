#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}


namespace k4n::thread{

class Processing
{
public:
  //Constructor / Destructor
  Processing(k4n::Node* node_k4n);
  ~Processing();

public:
  //Main function
  void start_thread();
  void run_thread();

  //Subfunction

private:
  k4n::dev::Swarm* k4n_swarm;

  std::thread thread;
};

}
