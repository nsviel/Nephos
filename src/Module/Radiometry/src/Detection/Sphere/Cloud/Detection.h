#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Sensor;}
namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::sphere{class Glyph;}
namespace rad::detection::cloud{class Ransac;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace utl::thread{class Pool;}


namespace rad::detection::cloud{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::detection::Node* node_detection);
  ~Detection();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void validate_bbox(dyn::base::Sensor* sensor);

private:
  utl::thread::Pool* thread_pool;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  rad::detection::sphere::Glyph* rad_glyph;
  rad::detection::cloud::Ransac* rad_ransac;
  rad::detection::Structure* rad_struct;

  std::thread thread;
  bool thread_idle = true;
};

}
