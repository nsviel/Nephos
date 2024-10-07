#include "Texture.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::color{

//Constructor / Destructor
Texture::Texture(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->k4n_format = new k4n::color::Format(node_k4n);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::retrieve_image(k4n::base::Sensor& sensor){
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

}
