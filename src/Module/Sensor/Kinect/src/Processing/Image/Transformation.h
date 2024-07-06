#pragma once

#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>
#include <stdint.h>
#include <vector>
#include <string>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::structure{class Sensor;}


namespace k4n::processing{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation(k4n::Node* node_k4n);
  ~Transformation();

public:
  //Main function
  void find_depth_to_color(k4n::structure::Sensor* sensor);
  void find_depth_and_ir_to_color(k4n::structure::Sensor* sensor);
  void find_ir_to_color(k4n::structure::Sensor* sensor);
  void find_color_to_depth(k4n::structure::Sensor* sensor);

  //Subfunction
  void retrieve_bgra_from_mjpeg(k4a::image& image, std::vector<uint8_t>& data);
  uint8_t* retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height);

private:
  k4n::Structure* k4n_struct;

  tjhandle tj_handle;
  bool thread_idle = true;
};

}
