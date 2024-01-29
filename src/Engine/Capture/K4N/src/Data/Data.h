#pragma once

#include <Utility/Specific/common.h>
#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>

namespace eng::k4n::dev{class Sensor;}


namespace eng::k4n::data{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //Main function
  void find_data_from_capture(eng::k4n::dev::Sensor* device, k4a::capture capture);

  //Data function
  void find_depth(eng::k4n::dev::Sensor* sensor, k4a::capture capture);
  void find_color(eng::k4n::dev::Sensor* sensor, k4a::capture capture);
  void find_ir(eng::k4n::dev::Sensor* sensor, k4a::capture capture);

  //Transformed data
  void find_depth_to_color(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation);
  void find_depth_to_color_custom(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation);
  void find_ir_to_color(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation);
  void find_color_to_depth(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation);

  //Subfunction
  string retrieve_format_from_k4a(k4a_image_format_t color_format);
  void retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, string& format);
  void retrieve_bgra_from_mjpeg(k4a::image& image, vector<uint8_t>& data);

private:
  tjhandle tj_handle;
};

}
