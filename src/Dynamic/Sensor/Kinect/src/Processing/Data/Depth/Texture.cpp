#include "Texture.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::depth{

//Constructor / Destructor
Texture::Texture(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->dat_depth = node_image->get_dat_depth();

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Depth::retrieve_raw_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Depth> image = sensor.depth.texture.depth;
  //---------------------------

  //Image
  this->convert_buffer_into_uint16(sensor);
  image->size = image->data.size();
  image->width = sensor.depth.data.width;
  image->height = sensor.depth.data.height;
  image->format = "R16_UINT";
  dat_depth->add_depth(sensor, image);

  //---------------------------
}
void Depth::retrieve_colored_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Image> image = sensor.depth.texture.image;
  //---------------------------

  //Image
  this->convert_buffer_into_color(sensor);
  image->size = image->data.size();
  image->width = sensor.depth.data.width;
  image->height = sensor.depth.data.height;
  image->format = "RGBA8";
  image->timestamp = sensor.depth.data.timestamp;
  dat_image->add_image(sensor, image);

  //---------------------------
}

}
