#pragma once

#include <memory>
#include <thread>

namespace k4n{class Node;}
namespace k4n::capture{class Sensor;}
namespace dat::elm{class Set;}
namespace dat::gph{class Graph;}
namespace dat::base{class Set;}
namespace io::imp{class Operation;}


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
  void manage_set_parent(k4n::capture::Sensor& sensor);

private:
  k4n::Node* node_k4n;
  dat::elm::Set* dat_set;
  dat::gph::Graph* dat_graph;
  io::imp::Operation* io_operation;

  std::thread thread;
  bool thread_running = false;
  bool flag = false;
  int current_nb_dev = 0;
};

}
