#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}


namespace k4n::dev{

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
  void manage_new_dev(int number);
  void manage_less_dev(int number);

private:
  k4n::dev::Swarm* k4n_swarm;

  std::thread thread;
  bool thread_running = false;
  int nb_dev = 0;
};

}
