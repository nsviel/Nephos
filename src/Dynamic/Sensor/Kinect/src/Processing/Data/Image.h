#pragma once

#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::processing{class Table_xy;}
namespace k4n::color{class Data;}
namespace k4n::depth{class Data;}
namespace k4n::infrared{class Data;}
namespace k4n::transformation{class Depth_to_color;}
namespace k4n::transformation{class Color_to_depth;}
namespace dat::base{class Sensor;}


namespace k4n::data{

class Image
{
public:
  //Constructor / Destructor
  Image(k4n::Node* node_k4n);
  ~Image();

public:
  //Main function
  void extract_data(dat::base::Sensor& sensor);

  //Subfunction
  void make_transformation(k4n::base::Sensor& sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::Table_xy* k4n_table;
  k4n::color::Data* k4n_color;
  k4n::depth::Data* k4n_depth;
  k4n::infrared::Data* k4n_ir;
  k4n::transformation::Depth_to_color* k4n_depth_to_color;
  k4n::transformation::Color_to_depth* k4n_color_to_depth;
};

}
