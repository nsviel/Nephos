#pragma once

#include <memory>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::base{class Sensor;}
namespace rad::cor{class Correction;}
namespace dat::img{class Image;}


namespace dyn::prc::cloud{

class Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(dyn::prc::Node* node_processing);
  ~Radiometry();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void compute_correction(std::shared_ptr<dat::base::Sensor> sensor);

private:
  dyn::prc::Structure* dyn_struct;
  rad::cor::Correction* rad_correction;
  dat::img::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
