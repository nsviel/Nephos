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
  this->k4a_format = new k4n::color::Format(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(dat::base::Sensor& dat_sensor){
  //---------------------------

  k4n::colornew::Structure color;
  color.sensor = dynamic_cast<k4n::base::Sensor*>(&dat_sensor);

  this->retrieve_data(color);
  this->retrieve_image(color);
  this->retrieve_color(color);
  this->retrieve_timestamp(color);

  //---------------------------
}

//Subfunction
void Data::retrieve_data(k4n::colornew::Structure& color){
  //---------------------------

  //Get k4a image
  color.image = color.sensor->device.capture->get_color_image();
  if(!color.image.is_valid()) return;

  //Data
  color.size = color.image.get_size();
  color.width = color.image.get_width_pixels();
  color.height = color.image.get_height_pixels();
  color.buffer = color.image.get_buffer();
  color.format = k4a_format->retrieve_format(color.image.get_format());
  color.timestamp = static_cast<float>(color.image.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}
void Data::retrieve_image(k4n::colornew::Structure& color){
/*  std::shared_ptr<utl::base::Image> image = color.texture.image;
  //---------------------------

  image->width = color.width;
  image->height = color.height;
  image->format = color.format;
  image->timestamp = color.timestamp;
  k4a_format->convert_bgra_to_rgba(color);
  dat_image->add_image(*color.sensor, image);
*/
  //---------------------------
}
void Data::retrieve_color(k4n::colornew::Structure& color){
/*  const uint8_t* buffer_color = sensor.color.data.buffer;
  //---------------------------
k4n::structure::Buffer buffer;
buffer.rgb.resize(sensor.cloud.size);
buffer.rgba.resize(sensor.cloud.size);

  #pragma omp parallel for
  for(int i=0; i<sensor.cloud.size; i++){
    //Raw values
    int idx = i * 4;
    float r = static_cast<float>(buffer_color[idx + 2]) / 255.0f;
    float g = static_cast<float>(buffer_color[idx + 1]) / 255.0f;
    float b = static_cast<float>(buffer_color[idx + 0]) / 255.0f;

    //Store
    buffer.rgb[i] = glm::vec3(r, g, b);
    buffer.rgba[i] = glm::vec4(r, g, b, 1);
  }*/

  //---------------------------
}
void Data::retrieve_timestamp(k4n::colornew::Structure& color){
  //---------------------------

  //color.sensor->timestamp.current = sensor.color.data.timestamp;

  //---------------------------
}

}
