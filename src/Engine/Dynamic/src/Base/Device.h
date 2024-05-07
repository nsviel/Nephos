#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}


namespace dyn::base{

class Device
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
  void start_thread(dat::base::Sensor* sensor);
  void run_thread(dat::base::Sensor* sensor);
  void stop_thread();
  void wait_thread();

  //Subfunction
  virtual void thread_init(dat::base::Sensor* sensor){}
  virtual void thread_loop(dat::base::Sensor* sensor){}
  virtual void thread_end(dat::base::Sensor* sensor){}

  inline bool is_thread_running(){return thread_running;}
  inline bool is_thread_paused(){return thread_paused;}

protected:
  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
};


}
