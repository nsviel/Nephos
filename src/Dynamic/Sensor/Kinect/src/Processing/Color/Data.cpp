#include "Data.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::image{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->k4a_format = new k4a::color::Format(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_image(sensor);
  this->retrieve_color(sensor);
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
  sensor.color.data.name = "color";
  sensor.color.data.k4a_image = color;
  sensor.color.data.size = color.get_size();
  sensor.color.data.width = color.get_width_pixels();
  sensor.color.data.height = color.get_height_pixels();
  sensor.color.data.buffer = color.get_buffer();
  sensor.color.data.format = k4a_format->retrieve_format(color.get_format());
  sensor.color.data.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}
void Data::retrieve_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Image>& image = sensor.color.image;
  //---------------------------

  k4a::image color = sensor.device.capture->get_color_image();
  if(!color.is_valid()) return;

  //Image
  image->width = sensor.color.data.width
  image->height = sensor.color.data.height
  image->format = rsensor.color.data.format
  image->timestamp = sensor.color.data.timestamp;
  k4a_format->convert_bgra_to_rgba(sensor);
  dat_image->add_image(sensor, image);

  //---------------------------
}
void Data::retrieve_color(k4n::base::Sensor& sensor){
  const uint8_t* buffer_color = sensor.color.data.buffer;
  //---------------------------

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
  }

  //---------------------------
}
void Data::retrieve_timestamp(k4n::base::Sensor& sensor){
  //---------------------------

  sensor.timestamp.current = sensor.color.data.timestamp;

  //---------------------------
}

}
