#include "Color.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Color::Color(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::extract_data(k4n::structure::Sensor* sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_image(sensor);

  //Current timestamp
  sensor->timestamp.current = sensor->color.data.timestamp;

  //---------------------------
}

//Subfunction
void Color::retrieve_data(k4n::structure::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image color = sensor->device.capture->get_color_image();
  if(!color.is_valid()) return;

  //Data
  sensor->color.data.name = "color";
  sensor->color.data.k4a_image = color;
  sensor->color.data.size = color.get_size();
  sensor->color.data.width = color.get_width_pixels();
  sensor->color.data.height = color.get_height_pixels();
  sensor->color.data.buffer = color.get_buffer();
  sensor->color.data.format = retrieve_format(color.get_format());
  sensor->color.data.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}
void Color::retrieve_image(k4n::structure::Sensor* sensor){
  //---------------------------

  //Image
  sensor->color.image.name = "Color";
  sensor->color.image.data = std::vector<uint8_t>(sensor->color.data.buffer, sensor->color.data.buffer + sensor->color.data.size);
  sensor->color.image.size = sensor->color.image.data.size();
  sensor->color.image.width = sensor->color.data.width;
  sensor->color.image.height = sensor->color.data.height;
  sensor->color.image.format = sensor->color.data.format;
  sensor->color.image.type = utl::media::COLOR;
  sensor->color.image.timestamp = sensor->color.data.timestamp;
  dat_image->add_image(sensor, &sensor->color.image);

  //---------------------------
}
std::string Color::retrieve_format(k4a_image_format_t color_format){
  std::string format = "";
  //---------------------------

  if(color_format == K4A_IMAGE_FORMAT_COLOR_MJPG){
    format = "MJPEG";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_NV12){
    format = "NV12";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_YUY2){
    format = "YUY2";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_BGRA32){
    format = "B8G8R8A8_SRGB";
  }else{
    std::cout<<"[error] kinect color image format"<<std::endl;
  }

  //---------------------------
  return format;
}

}
