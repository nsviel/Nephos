#pragma once

#include <Utility/Specific/common.h>


namespace eng::thread{

class Thread
{
public:
  //Constructor / Destructor
  Thread(bool* running);
  ~Thread();

public:
  //Main function
  void start();
  void run();
  void stop();
  void wait();

private:
  std::thread thread;
  bool* running;
  bool thread_idle = true;
};


}
