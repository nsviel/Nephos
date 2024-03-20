#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::structure{class Struct_k4n;}
namespace eng::scene{class Set;}


namespace k4n::thread{

class Connection
{
public:
  //Constructor / Destructor
  Connection(k4n::Node* node_k4n);
  ~Connection();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

private:
  k4n::structure::Struct_k4n* k4n_struct;
  k4n::dev::Swarm* k4n_swarm;
  eng::scene::Set* sce_set;

  std::thread thread;
  bool thread_running = false;
};

}
