#pragma once

#include <Dynamic/src/Base/Recorder.h>
#include <thread>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace utl::thread{class Pool;}


namespace dyn::cloud{

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
  void check_path(dyn::base::Sensor* sensor);
  void make_recording(dyn::base::Sensor* sensor);

private:
  dyn::Structure* dyn_struct;

  utl::thread::Pool* thread_pool;
  bool thread_idle = true;
};

}
