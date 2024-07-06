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
namespace utl::thread{class Pool;}
namespace dyn::image{class Operation;}
namespace dat::element{class Image;}


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

  //Subfunction
  std::string retrieve_format_from_k4a(k4a_image_format_t color_format);
  void retrieve_data_from_capture(k4a::image& image, std::vector<uint8_t>& data, std::string& format);
  void retrieve_bgra_from_mjpeg(k4a::image& image, std::vector<uint8_t>& data);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::Cloud* k4n_cloud;
  k4n::processing::Operation* k4n_operation;
  utl::thread::Pool* thread_pool;
  dyn::image::Operation* dyn_operation;
  dat::element::Image* dat_image;
  k4n::processing::image::Transformation* k4n_transformation;

  tjhandle tj_handle;
  bool thread_idle = true;
};

}
