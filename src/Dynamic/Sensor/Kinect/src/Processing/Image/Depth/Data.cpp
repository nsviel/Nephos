#include "Data.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::depth{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->dat_depth = node_image->get_dat_depth();
  this->k4n_format = new k4n::depth::Format(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_raw_image(sensor);
  this->retrieve_colored_image(sensor);

  //---------------------------
}

//Subfunction
void Data::retrieve_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Get k4a image
  k4a::image depth = sensor.device.capture->get_depth_image();
  if(!depth.is_valid()) return;

  //Data
  sensor.depth.data.image = depth;
  sensor.depth.data.width = depth.get_width_pixels();
  sensor.depth.data.height = depth.get_height_pixels();
  sensor.depth.data.buffer = depth.get_buffer();
  sensor.depth.data.size = depth.get_size();
  sensor.depth.data.format = k4n_format->retrieve_format(depth.get_format());
  sensor.depth.data.temperature = sensor.device.capture->get_temperature_c();
  sensor.depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  type::uint8_to_vec_uint16(sensor.depth.data.buffer, sensor.depth.data.size, sensor.info.buffer_depth);

  //---------------------------
}
void Data::retrieve_raw_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Depth> image = sensor.depth.texture.depth;
  //---------------------------

  //Image
  k4n_format->convert_buffer_into_uint16(sensor);
  image->size = image->data.size();
  image->width = sensor.depth.data.width;
  image->height = sensor.depth.data.height;
  image->format = "R16_UINT";
  dat_depth->add_depth(sensor, image);

  //---------------------------
}
void Data::retrieve_colored_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Image> image = sensor.depth.texture.image;
  //---------------------------

  //Image
  k4n_format->convert_buffer_into_color(sensor);
  image->size = image->data.size();
  image->width = sensor.depth.data.width;
  image->height = sensor.depth.data.height;
  image->format = "RGBA8";
  image->timestamp = sensor.depth.data.timestamp;
  dat_image->add_image(sensor, image);

  //---------------------------
}

}
