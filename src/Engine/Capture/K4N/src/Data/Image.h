#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::data{class Depth;}
namespace eng::k4n::data{class Infrared;}


namespace eng::k4n::data{

class Image
{
public:
  //Constructor / Destructor
  Image();
  ~Image();

public:
  //Main function
  void make_images(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::data::Depth* k4a_depth;
  eng::k4n::data::Infrared* k4a_infrared;
};

}
