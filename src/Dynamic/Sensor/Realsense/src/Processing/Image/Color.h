#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace dat::base{class Sensor;}
namespace dat::img{class Image;}
namespace utl::base{class Image;}


namespace rlx::processing{

class Color
{
public:
  //Constructor / Destructor
  Color(rlx::Node* node_realsense);
  ~Color();

public:
  //Main function
  void extract_data(dat::base::Sensor& sensor);

  //Subfunction
  std::string retrieve_format(rs2_format color_format);
  void retrieve_data(rs2::frame& frame, std::string format, std::shared_ptr<utl::base::Image> image);

private:
  rlx::Structure* rlx_struct;
  dat::img::Image* dat_image;
};

}
