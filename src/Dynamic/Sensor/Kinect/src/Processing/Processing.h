#pragma once

#include <Processing/src/Thread/Routine.h>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace k4n::processing::cloud{class Data;}
namespace k4n::processing::image{class Data;}
namespace dyn::prc::image{class Operation;}
namespace dyn::prc::cloud{class Operation;}
namespace sys::thread::task{class Pool;}


namespace k4n{

class Processing : public dyn::prc::thread::Routine
{
public:
  //Constructor / Destructor
  Processing(k4n::Node* node_k4n);
  ~Processing();

public:
  //Main function
  void start_thread(k4n::base::Sensor* sensor);
  void run_thread(k4n::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void image_processing(k4n::base::Sensor* sensor);
  void cloud_processing(k4n::base::Sensor* sensor);

private:
  k4n::processing::image::Data* k4n_image;
  k4n::processing::cloud::Data* k4n_cloud;
  sys::thread::task::Pool* thread_pool;
  dyn::prc::image::Operation* dyn_ope_image;
  dyn::prc::cloud::Operation* dyn_ope_cloud;

  bool thread_idle = true;
};

}
