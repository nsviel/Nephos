#include "Infrared.h"

#include <Realsense/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::processing{

//Constructor / Destructor
Infrared::Infrared(rlx::Node* node_realsense){
  //---------------------------

  dat::Node* node_data = node_realsense->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Infrared::~Infrared(){}

//Main function
void Infrared::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  std::shared_ptr<utl::media::Image> image = rlx_sensor->image.depth;
  //---------------------------

  // Get color and depth frames
  rs2::video_frame frame = rlx_sensor->device.frame_set.get_infrared_frame();
  if(!frame) return;
  std::string format = retrieve_format(frame.get_profile().format());

  //Image
  image->name = "Infrared";
  image->timestamp = frame.get_timestamp();
  image->width = frame.as<rs2::video_frame>().get_width();
  image->height = frame.as<rs2::video_frame>().get_height();
  this->retrieve_data(frame, format, image);
  dat_image->add_image(sensor, image);

  //---------------------------
}

//Subfunction
std::string Infrared::retrieve_format(rs2_format depth_format){
  std::string format = "";
  //---------------------------

  switch(depth_format){
    case RS2_FORMAT_Y8:{
      format = "DEPTHY8";
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
void Infrared::retrieve_data(rs2::frame& frame, std::string format, std::shared_ptr<utl::media::Image> image){
  //---------------------------

  std::vector<uint8_t> buffer;
  this->convert_image_into_color(frame, buffer);

  image->format = "R8G8B8A8_SRGB";
  image->data = buffer;
  image->size = buffer.size();

  //---------------------------
}
void Infrared::convert_image_into_color(rs2::frame& frame, std::vector<uint8_t>& buffer){
  //---------------------------

  const uint8_t* data = reinterpret_cast<const uint8_t*>(frame.get_data());
  int size = frame.get_data_size();
  buffer = std::vector<uint8_t>(size * 4, 0);

  for(int i=0, j=0; i<size; i++, j+=4){
    float r = static_cast<float>(data[i]);

    // Set RGBA values; since it's grayscale, R, G, and B are the same
    buffer[j]     = static_cast<uint8_t>(r);   // R
    buffer[j + 1] = static_cast<uint8_t>(r);   // G
    buffer[j + 2] = static_cast<uint8_t>(r);   // B
    buffer[j + 3] = 255;
  }

  //---------------------------
}

}
