#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}


namespace k4n::thread{

class Postprocessing
{
public:
  //Constructor / Destructor
  Postprocessing(k4n::Node* node_k4n);
  ~Postprocessing();

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
