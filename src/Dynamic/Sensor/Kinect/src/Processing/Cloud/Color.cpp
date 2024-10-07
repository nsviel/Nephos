#include "Color.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::cloud{

//Constructor / Destructor
Color::Color(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->atr_field = new dat::atr::Field();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->extraction_data(sensor);
  this->extraction_transfer(sensor);

  //---------------------------
}

//Subfunction
void Color::extraction_data(k4n::base::Sensor& sensor){
  const uint8_t* buffer_color = sensor.color.data.buffer;
  //---------------------------

  sensor.color.data.rgb.resize(sensor.depth.cloud.size);
  sensor.color.data.rgba.resize(sensor.depth.cloud.size);

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor.depth.cloud.size; i++){
    //Raw values
    int idx = i * 4;
    float r = static_cast<float>(buffer_color[idx + 2]) / 255.0f;
    float g = static_cast<float>(buffer_color[idx + 1]) / 255.0f;
    float b = static_cast<float>(buffer_color[idx + 0]) / 255.0f;

    //Store
    sensor.color.data.rgb[i] = glm::vec3(r, g, b);
    sensor.color.data.rgba[i] = glm::vec4(r, g, b, 1);
  }

  //---------------------------
}
void Color::extraction_transfer(k4n::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data.mutex);

  data.rgb = sensor.color.data.rgb;
  data.rgba = sensor.color.data.rgba;

  //---------------------------
}


}
