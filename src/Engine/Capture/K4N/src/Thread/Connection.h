#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n::dev{

class Connection
{
public:
  //Constructor / Destructor
  Connection(eng::k4n::Node* node_k4n);
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
  eng::k4n::dev::Swarm* k4n_swarm;

  std::thread thread;
  bool thread_running = false;
  int nb_dev = 0;
};

}
