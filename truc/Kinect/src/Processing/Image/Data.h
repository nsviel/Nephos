#pragma once

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::processing::image{class Color;}
namespace k4n::processing::image{class Depth;}
namespace k4n::processing::image{class Infrared;}
namespace k4n::processing::image{class Depth_to_color;}
namespace k4n::processing::image{class Color_to_depth;}


namespace k4n::processing::image{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void extract_data(k4n::base::Sensor* device);

  //Subfunction
  void extract_image_data(k4n::base::Sensor* sensor);
  void make_transformation(k4n::base::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::image::Color* k4n_color;
  k4n::processing::image::Depth* k4n_depth;
  k4n::processing::image::Infrared* k4n_ir;
  k4n::processing::image::Depth_to_color* k4n_depth_to_color;
  k4n::processing::image::Color_to_depth* k4n_color_to_depth;
};

}