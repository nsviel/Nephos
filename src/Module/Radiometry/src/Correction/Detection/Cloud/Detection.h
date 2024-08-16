#pragma once

#include <thread>

namespace dyn::prc::base{class Sensor;}
namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Glyph;}
namespace rad::correction::cloud{class Ransac;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace sys::thread::task{class Pool;}


namespace rad::correction::cloud{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::correction::Node* node_correction);
  ~Detection();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void validate_bbox(dyn::base::Sensor* sensor);

private:
  sys::thread::task::Pool* thread_pool;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  rad::correction::Glyph* rad_glyph;
  rad::correction::cloud::Ransac* rad_ransac;
  rad::correction::Structure* rad_struct;

  std::thread thread;
  bool thread_idle = true;
};

}
