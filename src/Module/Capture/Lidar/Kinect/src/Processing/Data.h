#pragma once

#include <Utility/Specific/Common.h>
#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>

namespace k4n::structure{class K4N;}
namespace k4n{class Node;}
namespace k4n::dev{class Device;}
namespace k4n::processing{class Cloud;}
namespace k4n::processing{class Image;}
namespace utl::thread{class Pool;}


namespace k4n::processing{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void start_thread(k4n::dev::Device* sensor);
  void run_thread(k4n::dev::Device* sensor);
  void wait_thread();

  //Data function
  void find_data_from_capture(k4n::dev::Device* device);
  void find_data_depth(k4n::dev::Device* sensor);
  void find_data_color(k4n::dev::Device* sensor);
  void find_data_ir(k4n::dev::Device* sensor);

  //Transformed data
  void find_data_cloud(k4n::dev::Device* sensor);
  void find_depth_to_color(k4n::dev::Device* sensor);
  void find_depth_and_ir_to_color(k4n::dev::Device* sensor);
  void find_ir_to_color(k4n::dev::Device* sensor);
  void find_color_to_depth(k4n::dev::Device* sensor);

  //Subfunction
  string retrieve_format_from_k4a(k4a_image_format_t color_format);
  void retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, string& format);
  void retrieve_bgra_from_mjpeg(k4a::image& image, vector<uint8_t>& data);
  uint8_t* retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height);

private:
  k4n::processing::Cloud* k4n_cloud;
  k4n::processing::Image* k4n_image;
  utl::thread::Pool* thread_pool;

  tjhandle tj_handle;
  bool idle = true;
};

}
