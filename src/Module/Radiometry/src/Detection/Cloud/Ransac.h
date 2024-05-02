#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace k4n::dev{class Sensor;}
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
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void ransac_sphere(k4n::dev::Sensor* sensor);

private:
  utl::thread::Pool* thread_pool;
  rad::Structure* radio_struct;
  rad::detection::cloud::Glyph* radio_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  ope::attribut::Normal* ope_normal;

  bool idle = true;
  int step;
  vec3 current_pose;
  float radius;
};

}
