#pragma once

#include <Utility/Specific/common.h>


namespace eng::thread{

class Thread
{
public:
  //Constructor / Destructor
  Thread();
  ~Thread();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();
  void wait_thread();

private:
  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
};


}
