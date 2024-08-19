#pragma once

#include <Processing/src/Base/Recorder.h>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dyn::prc::base{class Sensor;}
namespace sys::thread::task{class Pool;}


namespace dyn::prc::cloud{

class Recorder : public dyn::prc::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder(dyn::prc::Node* node_processing);
  ~Recorder();

public:
  //Main function
  void start_thread(dyn::prc::base::Sensor* sensor);
  void run_thread(dyn::prc::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void compute_recording(dyn::prc::base::Sensor* sensor);

private:
  dyn::prc::Structure* dyn_struct;

  sys::thread::task::Pool* thread_pool;
  bool thread_idle = true;
};

}
