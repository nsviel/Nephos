#pragma once

#include <Utility/Specific/common.h>
#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>

namespace k4n::dev{class Sensor;}
namespace k4n::data{class Depth;}
namespace k4n::data{class Infrared;}
namespace k4n::data{class Cloud;}
namespace k4n::data{class Image;}


namespace k4n::data{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void run_thread(k4n::dev::Sensor* sensor, k4a::capture* capture);

  //Data function
  void find_data_from_capture(k4n::dev::Sensor* device, k4a::capture* capture);
  void find_data_depth(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void find_data_color(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void find_data_ir(k4n::dev::Sensor* sensor, k4a::capture* capture);

  //Transformed data
  void find_data_cloud(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void find_depth_to_color(k4n::dev::Sensor* sensor, k4a::capture* capture, k4a::transformation& transformation);
  void find_depth_and_ir_to_color(k4n::dev::Sensor* sensor, k4a::capture* capture, k4a::transformation& transformation);
  void find_ir_to_color(k4n::dev::Sensor* sensor, k4a::capture* capture, k4a::transformation& transformation);
  void find_color_to_depth(k4n::dev::Sensor* sensor, k4a::capture* capture, k4a::transformation& transformation);

  //Subfunction
  string retrieve_format_from_k4a(k4a_image_format_t color_format);
  void retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, string& format);
  void retrieve_bgra_from_mjpeg(k4a::image& image, vector<uint8_t>& data);
  uint8_t* retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height);

private:
  k4n::data::Depth* k4a_depth;
  k4n::data::Infrared* k4a_infrared;
  k4n::data::Cloud* k4a_cloud;
  k4n::data::Image* k4n_image;

  std::thread thread;
  bool thread_finished;
  tjhandle tj_handle;
};

}
