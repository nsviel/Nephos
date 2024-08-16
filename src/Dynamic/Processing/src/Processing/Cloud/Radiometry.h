#pragma once

#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dyn::prc::base{class Sensor;}
namespace rad::correction{class Correction;}
namespace dat::elm{class Image;}


namespace dyn::prc::cloud{

class Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(dyn::prc::Node* node_dynamic);
  ~Radiometry();

public:
  //Main function
  void start_thread(dyn::prc::base::Sensor* sensor);
  void run_thread(dyn::prc::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void compute_correction(dyn::prc::base::Sensor* sensor);

private:
  dyn::prc::Structure* dyn_struct;
  rad::correction::Correction* rad_correction;
  dat::elm::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
