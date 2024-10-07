#include "Data.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::color{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->k4n_format = new k4n::color::Format(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_image(sensor);
  this->retrieve_timestamp(sensor);

  //---------------------------
}

//Subfunction
void Data::retrieve_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Get k4a image
  k4a::image color = sensor.device.capture->get_color_image();
  if(!color.is_valid()) return;

  //Data
  sensor.color.data.image = color;
  sensor.color.data.size = color.get_size();
  sensor.color.data.width = color.get_width_pixels();
  sensor.color.data.height = color.get_height_pixels();
  sensor.color.data.buffer = color.get_buffer();
  sensor.color.data.format = k4n_format->retrieve_format(color.get_format());
  sensor.color.data.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}
void Data::retrieve_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Image>& image = sensor.color.texture.image;
  //---------------------------

  //Image
  image->width = sensor.color.data.width;
  image->height = sensor.color.data.height;
  image->format = sensor.color.data.format;
  image->timestamp = sensor.color.data.timestamp;
  k4n_format->convert_bgra_to_rgba(sensor);
  dat_image->add_image(sensor, image);

  //---------------------------
}
void Data::retrieve_timestamp(k4n::base::Sensor& sensor){
  //---------------------------

  sensor.timestamp.current = sensor.color.data.timestamp;

  //---------------------------
}

}
