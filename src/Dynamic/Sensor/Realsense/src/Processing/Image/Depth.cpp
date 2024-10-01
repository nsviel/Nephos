#include "Depth.h"

#include <Realsense/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::processing{

//Constructor / Destructor
Depth::Depth(rlx::Node* node_realsense){
  //---------------------------

  dat::Node* node_data = node_realsense->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  std::shared_ptr<utl::base::Image> image = rlx_sensor->image.depth;
  //---------------------------

  // Get color and depth frames
  rs2::depth_frame frame = rlx_sensor->device.frame_set.get_depth_frame();
  if(!frame) return;
  std::string format = retrieve_format(frame.get_profile().format());

  //Image
  image->timestamp = frame.get_timestamp();
  image->width = frame.as<rs2::video_frame>().get_width();
  image->height = frame.as<rs2::video_frame>().get_height();
  this->retrieve_data(frame, format, image);

  //---------------------------
}

//Subfunction
std::string Depth::retrieve_format(rs2_format depth_format){
  std::string format = "";
  //---------------------------

  switch(depth_format){
    case RS2_FORMAT_Z16:{
      format = "DEPTH16";
      break;
    }
    default:{
      std::cout<<"[error] kinect depth image format"<<std::endl;
      break;
    }
  }

  //---------------------------
  return format;
}
void Depth::retrieve_data(rs2::frame& frame, std::string format, std::shared_ptr<utl::base::Image> image){
  //---------------------------

  std::vector<uint8_t> buffer;
  this->convert_image_into_color(frame, buffer);

  image->format = "RGBA8";
  image->data = buffer;
  image->size = buffer.size();

  //---------------------------
}
void Depth::convert_image_into_color(rs2::frame& frame, std::vector<uint8_t>& buffer){
  //---------------------------

  const uint8_t* data = reinterpret_cast<const uint8_t*>(frame.get_data());
  int size = frame.get_data_size();
  float range_min = 0.4;
  float range_max = 10;

  buffer = std::vector<uint8_t>(size * 4, 0);

  for(int i=0, j=0; i<size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&data[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if(r != 0){
      uint16_t clamped = std::min(r, static_cast<uint16_t>(range_max * 1000)); // in mm
      clamped = std::max(clamped, static_cast<uint16_t>(range_min * 1000)); // in mm
      float hue = (clamped - range_min * 1000) / (range_max * 1000 - range_min * 1000);
      constexpr float range = 2.f / 3.f;
      hue *= range;
      hue = range - hue;

      ImGui::ColorConvertHSVtoRGB(hue, 1.f, 1.f, R, G, B);
    }

    buffer[j] = static_cast<uint8_t>(R * 255);
    buffer[j + 1] = static_cast<uint8_t>(G * 255);
    buffer[j + 2] = static_cast<uint8_t>(B * 255);
    buffer[j + 3] = 255;
  }

  //---------------------------
}

}
