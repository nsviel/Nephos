#pragma once

#include <memory>
#include <thread>

namespace dat::base{class Sensor;}
namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Glyph;}
namespace rad::cor::cloud{class Ransac;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace sys::thread::task{class Pool;}


namespace rad::cor::cloud{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::cor::Node* node_correction);
  ~Detection();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void validate_bbox(std::shared_ptr<dat::base::Sensor> sensor);

private:
  sys::thread::task::Pool* thread_pool;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  rad::cor::Glyph* rad_glyph;
  rad::cor::cloud::Ransac* rad_ransac;
  rad::cor::Structure* rad_struct;

  std::thread thread;
  bool thread_idle = true;
};

}
