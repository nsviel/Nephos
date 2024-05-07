#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace dat{class Set;}
namespace dat{class Graph;}


namespace k4n::capture{

class Synchro
{
public:
  //Constructor / Destructor
  Synchro(k4n::Node* node_k4n);
  ~Synchro();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

private:
  dat::Set* dat_set;
  dat::Graph* dat_graph;

  std::thread thread;
  bool thread_running = false;
};

}
