#pragma once

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace k4n::processing::image{class Transformation;}
namespace k4n::processing::image{class Color;}
namespace k4n::processing::image{class Depth;}
namespace k4n::processing::image{class Infrared;}


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
  k4n::processing::image::Transformation* k4n_transformation;
  k4n::processing::image::Color* k4n_color;
  k4n::processing::image::Depth* k4n_depth;
  k4n::processing::image::Infrared* k4n_ir;
};

}
