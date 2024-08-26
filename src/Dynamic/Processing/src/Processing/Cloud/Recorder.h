#pragma once

#include <Data/Base/Sensor/Recorder.h>
#include <memory>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::base{class Sensor;}
namespace sys::thread::task{class Pool;}


namespace dyn::prc::cloud{

class Recorder : public dat::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder(dyn::prc::Node* node_processing);
  ~Recorder();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void compute_recording(std::shared_ptr<dat::base::Sensor> sensor);

private:
  dyn::prc::Structure* dyn_struct;

  sys::thread::task::Pool* thread_pool;
  bool thread_idle = true;
};

}
