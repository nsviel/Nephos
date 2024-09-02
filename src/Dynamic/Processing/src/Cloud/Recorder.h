#pragma once

#include <Data/Sensor/Structure/Recorder.h>
#include <memory>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::base{class Sensor;}
namespace thr::task{class Pool;}


namespace dyn::prc::cloud{

class Recorder : public dat::sensor::Recorder
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

  thr::task::Pool* thread_pool;
  bool thread_idle = true;
};

}
