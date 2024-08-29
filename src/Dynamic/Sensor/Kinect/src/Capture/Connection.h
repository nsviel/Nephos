#pragma once

#include <memory>
#include <thread>

namespace k4n{class Node;}
namespace k4n{class Utils;}
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

private:
  k4n::Node* node_k4n;
  k4n::Utils* k4n_utils;
  io::imp::Operation* io_operation;

  std::thread thread;
  bool thread_running = false;
  bool flag = false;
  int current_nb_dev = 0;
};

}
