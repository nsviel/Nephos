#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace rad::detection::cloud{class Glyph;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace ope::attribut{class Normal;}


namespace rad::detection{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(rad::Node* node_radio);
  ~Ransac();

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor);
  void run_thread(dat::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void ransac_sphere(dat::base::Sensor* sensor);

private:
  utl::thread::Pool* thread_pool;
  rad::Structure* rad_struct;
  rad::detection::cloud::Glyph* rad_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  ope::attribut::Normal* ope_normal;

  bool idle = true;
  int step;
  vec3 current_pose;
  float radius;
};

}
