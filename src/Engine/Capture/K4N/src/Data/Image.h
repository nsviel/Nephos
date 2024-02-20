#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace k4n::dev{class Sensor;}
namespace k4n::data{class Depth;}
namespace k4n::data{class Infrared;}


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
  void make_images(k4n::dev::Sensor* sensor);

  //Subfunction
  void copy_image_color(k4n::dev::Sensor* sensor);
  void copy_image_depth(k4n::dev::Sensor* sensor);
  void copy_image_ir(k4n::dev::Sensor* sensor);

private:
  k4n::data::Depth* k4a_depth;
  k4n::data::Infrared* k4a_infrared;

  std::thread thread;
};

}
