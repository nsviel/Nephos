#pragma once

#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Utility/Specific/common.h>
#include <image/turbojpeg.h>


namespace eng::kinect::data{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //Main function
  void find_data_from_capture(K4A_device* device, k4a::capture capture);

  //Data function
  void find_depth(K4A_device* k4a_device, k4a::capture capture);
  void find_color(K4A_device* k4a_device, k4a::capture capture);
  void find_color_from_depth(K4A_device* k4a_device, k4a::capture capture);
  void find_ir(K4A_device* k4a_device, k4a::capture capture);

  //Subfunction
  string convert_k4a_format(k4a_image_format_t color_format);
  k4a::image retrieve_image_from_capture(k4a::image& image);
  vector<uint8_t> retrieve_data_from_capture(k4a::image& image);
  vector<uint8_t> convert_mjpeg_image(k4a::image& image);

private:
  tjhandle tj_handle;
};

}
