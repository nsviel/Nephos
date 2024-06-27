#pragma once

#include <thread>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace rad::correction{class Correction;}
namespace dat{class Image;}


namespace dyn::cloud{

class Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(dyn::Node* node_dynamic);
  ~Radiometry();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

private:
  dyn::Structure* dyn_struct;
  rad::correction::Correction* rad_correction;
  dat::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
