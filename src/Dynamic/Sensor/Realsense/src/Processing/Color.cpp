#include "Color.h"

#include <Realsense/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::processing{

//Constructor / Destructor
Color::Color(rlx::Node* node_realsense){
  //---------------------------

  dat::Node* node_data = node_realsense->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_image = node_element->get_dat_image();
  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  std::shared_ptr<utl::media::Image> image = rlx_sensor->image.color;
  //---------------------------

  // Get color frame
  rs2::video_frame frame = rlx_sensor->device.frameset.get_color_frame();
  if(!frame) return;
  std::string format = retrieve_format(frame.get_profile().format());

  //Image
  image->name = "Color";
  image->timestamp = frame.get_timestamp();
  image->width = frame.as<rs2::video_frame>().get_width();
  image->height = frame.as<rs2::video_frame>().get_height();
  this->retrieve_data(frame, format, image);
  dat_image->add_image(sensor, image);

  //---------------------------
}

//Subfunction
std::string Color::retrieve_format(rs2_format color_format){
  std::string format = "";
  //---------------------------

  switch(color_format) {
    case RS2_FORMAT_RGB8: {
      format = "R8G8B8_SRGB";
      break;
    }
    case RS2_FORMAT_BGR8: {
      format = "B8G8R8A8_SRGB";
      break;
    }
    case RS2_FORMAT_RGBA8: {
      format = "R8G8B8A8_SRGB";
      break;
    }
    case RS2_FORMAT_BGRA8: {
      format = "BGRA8";
      break;
    }
    case RS2_FORMAT_YUYV: {
      format = "YUYV";
      break;
    }
    case RS2_FORMAT_MJPEG: {
      format = "MJPEG";
      break;
    }
    case RS2_FORMAT_Z16: {
      format = "Z16";
      break;
    }
    default: {
      std::cerr << "[error] Unsupported RealSense color format" << std::endl;
      break;
    }
  }

  //---------------------------
  return format;
}
void Color::retrieve_data(rs2::frame& frame, std::string format, std::shared_ptr<utl::media::Image> image){
  //---------------------------

  const uint8_t* data = reinterpret_cast<const uint8_t*>(frame.get_data());
  std::vector<uint8_t> buffer;
  int size = frame.get_data_size();

  // Process the data based on the format
  if (format == "R8G8B8_SRGB") {
    int pixel_count = size / 3;
    buffer = std::vector<uint8_t>(pixel_count * 4);

    // Copy and add alpha channel (255, fully opaque) to each pixel
    for (int i = 0; i < pixel_count; ++i) {
      buffer[i * 4 + 0] = data[i * 3 + 0]; // R
      buffer[i * 4 + 1] = data[i * 3 + 1]; // G
      buffer[i * 4 + 2] = data[i * 3 + 2]; // B
      buffer[i * 4 + 3] = 255;             // A (fully opaque)
    }
  } else {
    buffer = std::vector<uint8_t>(size);
    std::copy(data, data + size, buffer.begin());
  }

  image->format = "R8G8B8A8_SRGB";
  image->data = buffer;
  image->size = buffer.size();

  //---------------------------
}

}
