#pragma once

#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>
#include <stdint.h>
#include <vector>
#include <string>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing{class Cloud;}
namespace k4n::processing{class Operation;}
namespace k4n::processing::image{class Transformation;}
namespace k4n::processing::image{class Format;}
namespace k4n::processing::image{class Color;}
namespace k4n::processing::image{class Depth;}
namespace k4n::processing::image{class Infrared;}
namespace utl::thread{class Pool;}
namespace dyn::image{class Operation;}
namespace dat::element{class Image;}


namespace k4n::processing::image{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void find_data_from_capture(k4n::structure::Sensor* device);

  //Subfunction
  void find_data_cloud(k4n::structure::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::Cloud* k4n_cloud;
  k4n::processing::Operation* k4n_operation;
  k4n::processing::image::Format* k4n_format;
  dat::element::Image* dat_image;
  k4n::processing::image::Transformation* k4n_transformation;
  k4n::processing::image::Color* k4n_color;
  k4n::processing::image::Depth* k4n_depth;
  k4n::processing::image::Infrared* k4n_ir;
};

}
