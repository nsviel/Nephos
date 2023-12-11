#pragma once

#include <Utility/Specific/common.h>

class K4A_swarm;


class K4A_connection
{
public:
  //Constructor / Destructor
  K4A_connection(K4A_swarm* k4a_swarm);
  ~K4A_connection();

public:
  //Main function
  void run();

  //Subfunction
  void start_thread();
  void run_thread();
  void stop_thread();

  inline bool is_thread_running(){return thread_running;}

private:
  K4A_swarm* k4a_swarm;

  std::thread thread;
  bool thread_running = false;
};
