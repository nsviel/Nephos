#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace dat::base{class Sensor;}
namespace dat::img{class Image;}
namespace utl::media{class Image;}


namespace rlx::processing{

class Depth
{
public:
  //Constructor / Destructor
  Depth(rlx::Node* node_realsense);
  ~Depth();

public:
  //Main function
  void extract_data(dat::base::Sensor& sensor);

  //Subfunction
  std::string retrieve_format(rs2_format depth_format);
  void retrieve_data(rs2::frame& frame, std::string format, std::shared_ptr<utl::media::Image> image);
  void convert_image_into_color(rs2::frame& frame, std::vector<uint8_t>& buffer);

private:
  rlx::Structure* rlx_struct;
  dat::img::Image* dat_image;
};

}
