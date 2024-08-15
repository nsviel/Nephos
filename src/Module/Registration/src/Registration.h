#pragma once

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace sys::thread::task{class Pool;}


namespace rad::processing{

class Registration
{
public:
  //Constructor / Destructor
  Registration(k4n::Node* node_k4n);
  ~Registration();

public:
  //Main function
  void start_thread(k4n::base::Sensor* sensor);
  void run_thread(k4n::base::Sensor* sensor);
  void wait_thread();

  //Subfunction


private:
  sys::thread::task::Pool* thread_pool;

  bool idle = true;
};

}
