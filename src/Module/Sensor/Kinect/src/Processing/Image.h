#pragma once

#include <Utility/Specific/Common.h>
#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing{class Cloud;}
namespace k4n::processing{class Operation;}
namespace utl::thread{class Pool;}
namespace dyn::image{class Operation;}
namespace dat{class Image;}


namespace k4n::processing{

class Image
{
public:
  //Constructor / Destructor
  Image(k4n::Node* node_k4n);
  ~Image();

public:
  //Main function
  void start_thread(k4n::structure::Sensor* sensor);
  void run_thread(k4n::structure::Sensor* sensor);
  void wait_thread();

  //Data function
  void find_data_from_capture(k4n::structure::Sensor* device);
  void find_data_depth(k4n::structure::Sensor* sensor);
  void find_data_color(k4n::structure::Sensor* sensor);
  void find_data_ir(k4n::structure::Sensor* sensor);
  void find_data_cloud(k4n::structure::Sensor* sensor);

  //Transformed data
  void find_depth_to_color(k4n::structure::Sensor* sensor);
  void find_depth_and_ir_to_color(k4n::structure::Sensor* sensor);
  void find_ir_to_color(k4n::structure::Sensor* sensor);
  void find_color_to_depth(k4n::structure::Sensor* sensor);

  //Subfunction
  std::string retrieve_format_from_k4a(k4a_image_format_t color_format);
  void retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, std::string& format);
  void retrieve_bgra_from_mjpeg(k4a::image& image, vector<uint8_t>& data);
  uint8_t* retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::Cloud* k4n_cloud;
  k4n::processing::Operation* k4n_operation;
  utl::thread::Pool* thread_pool;
  dyn::image::Operation* dyn_operation;
  dat::Image* dat_image;

  tjhandle tj_handle;
  bool idle = true;
};

}
