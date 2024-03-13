#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace k4n::dev{class Sensor;}
namespace k4n::data{class Depth;}
namespace k4n::data{class Infrared;}
namespace ope::attribut{class Fitting;}


namespace k4n::data{

class Image
{
public:
  //Constructor / Destructor
  Image();
  ~Image();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread_idle();

  //Subfunction
  void copy_image_color(k4n::dev::Sensor* sensor);
  void copy_image_depth(k4n::dev::Sensor* sensor);
  void copy_image_ir(k4n::dev::Sensor* sensor);

private:
  k4n::data::Depth* k4a_depth;
  k4n::data::Infrared* k4a_infrared;
  ope::attribut::Fitting* ope_fitting;

  std::thread thread;
  bool thread_idle = true;
};

}
