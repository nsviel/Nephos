#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::structure{class Struct_k4n;}
namespace eng::scene{class Set;}


namespace k4n::thread{

struct Connected_device{
  //---------------------------

  string serial_number;
  int index;

  //---------------------------
};

class Connection
{
public:
  //Constructor / Destructor
  Connection(k4n::structure::Struct_k4n* struct_k4n);
  ~Connection();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

  //Subfunction
  void manage_new_dev();

private:
  k4n::structure::Struct_k4n* struct_k4n;
  k4n::dev::Swarm* k4n_swarm;
  eng::scene::Set* sce_set;

  std::thread thread;
  bool thread_running = false;
};

}
