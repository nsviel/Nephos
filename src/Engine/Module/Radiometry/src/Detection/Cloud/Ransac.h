#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace radio{class Structure;}
namespace k4n::dev{class Sensor;}
namespace k4n::thread{class Pool;}
namespace radio::detection::cloud{class Glyph;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace ope::attribut{class Normal;}


namespace radio::detection{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(radio::Structure* radio_struct);
  ~Ransac();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void ransac_sphere(k4n::dev::Sensor* sensor);

private:
  k4n::thread::Pool* k4n_pool;
  radio::Structure* radio_struct;
  radio::detection::cloud::Glyph* radio_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  ope::attribut::Normal* ope_normal;

  bool idle = true;
  int step;
  vec3 current_pose;
  float radius;
};

}
