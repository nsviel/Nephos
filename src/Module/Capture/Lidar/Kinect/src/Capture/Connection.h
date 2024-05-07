#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace dat{class Set;}
namespace dat{class Graph;}


namespace k4n::capture{

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

  //Subfunction
  void create_sensor(int index);
  void manage_connected_device();
  void manage_master();

private:
  k4n::structure::K4N* k4n_struct;
  dat::Set* dat_set;
  dat::Graph* dat_graph;

  std::thread thread;
  bool thread_running = false;
};

}
