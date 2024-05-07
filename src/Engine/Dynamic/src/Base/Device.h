#pragma once

#include <Data/src/Base/Entity.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}


namespace dyn::base{

class Device : public dat::base::Entity
{
public:
  //Constructor / Destructor
  Device();
  ~Device();

public:
  //Main function
  virtual void init(){}
  virtual void info(){}
  virtual void reset(){}

  //Thread function
  void start_thread();
  void run_thread();
  void stop_thread();
  void wait_thread();

  //Subfunction
  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}

  inline bool is_thread_running(){return thread_running;}
  inline bool is_thread_paused(){return thread_paused;}

protected:
  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
};


}
