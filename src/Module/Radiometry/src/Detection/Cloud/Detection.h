#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection::cloud{class Glyph;}
namespace rad::detection::cloud{class Ransac;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace utl::thread{class Pool;}


namespace rad::detection::cloud{

enum STEP{
  WAIT_VALIDATION = 0,
  PROCESSING = 1,
};

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor);
  void run_thread(dat::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void validate_bbox(dat::base::Sensor* sensor);

private:
  utl::thread::Pool* thread_pool;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  rad::detection::cloud::Glyph* rad_glyph;
  rad::detection::cloud::Ransac* rad_ransac;
  rad::Structure* rad_struct;

  bool thread_idle = true;
};

}
