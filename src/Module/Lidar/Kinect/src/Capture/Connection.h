#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
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
  void manage_connected_device();
  void create_sensor(int index);
  void manage_master();

private:
  dat::Set* dat_set;
  dat::Graph* dat_graph;

  std::thread thread;
  bool thread_running = false;
  bool flag = false;
  int current_nb_dev = 0;
};

}
