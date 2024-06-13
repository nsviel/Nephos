#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace dat{class Set;}
namespace dat{class Graph;}
namespace dat::base{class Set;}
namespace ldr::importer{class Operation;}


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
  dat::base::Set* manage_set_parent();

private:
  k4n::Node* node_k4n;
  dat::Set* dat_set;
  dat::Graph* dat_graph;
  ldr::importer::Operation* ldr_operation;

  std::thread thread;
  bool thread_running = false;
  bool flag = false;
  int current_nb_dev = 0;
};

}
