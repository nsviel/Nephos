#pragma once

#include <Dynamic/src/Base/Recorder.h>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dyn::prc::base{class Sensor;}
namespace sys::thread::task{class Pool;}


namespace dyn::prc::cloud{

class Recorder : public dyn::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder(dyn::Node* node_dynamic);
  ~Recorder();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void compute_recording(dyn::base::Sensor* sensor);

private:
  dyn::Structure* dyn_struct;

  sys::thread::task::Pool* thread_pool;
  bool thread_idle = true;
};

}
