#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Device/K4A_swarm.h>


namespace util::kinect::thread{

class Connection
{
public:
  //Constructor / Destructor
  Connection(K4A_swarm* k4a_swarm);
  ~Connection();

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

}
