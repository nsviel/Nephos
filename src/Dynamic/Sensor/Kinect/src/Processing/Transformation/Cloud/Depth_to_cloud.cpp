#include "Depth_to_cloud.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Depth_to_cloud::Depth_to_cloud(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_color = new k4n::cloud::Color(node_k4n);
  this->k4n_intensity = new k4n::cloud::Intensity(node_k4n);
  this->k4n_location = new k4n::cloud::Location(node_k4n);
  this->atr_field = new dat::atr::Field();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Depth_to_cloud::~Depth_to_cloud(){}

//Main function
void Depth_to_cloud::make_transformation(k4n::base::Sensor& sensor){
  //---------------------------

  if(check_condition(sensor) == false) return;
  this->extraction_init(sensor);

  //---------------------------
}

//Subfunction
bool Depth_to_cloud::check_condition(k4n::base::Sensor& sensor){
  //---------------------------

  if(!sensor.depth.data.image.is_valid()) return false;
  if(!sensor.infra.data.image.is_valid()) return false;
  if(sensor.color.data.buffer == nullptr) return false;
  if(sensor.color.data.size != sensor.depth.data.size * 2) return false;

  //---------------------------
  return true;
}
void Depth_to_cloud::extraction_init(k4n::base::Sensor& sensor){
  //---------------------------

  //Create cloud image
  sensor.depth.cloud.image = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM,
    sensor.depth.data.width,
    sensor.depth.data.height,
    sensor.depth.data.width * sizeof(int16_t) * 3
  );

  //Transform depth into cloud
  sensor.device.transformation.depth_image_to_point_cloud(sensor.depth.data.image, sensor.device.calibration_type, &sensor.depth.cloud.image);
  sensor.depth.cloud.buffer = sensor.depth.cloud.image.get_buffer();
  sensor.depth.cloud.size = sensor.depth.cloud.image.get_size() / (3 * sizeof(int16_t));

  //Resize vectors
  sensor.depth.data.xyz.resize(sensor.depth.cloud.size);
  sensor.depth.data.R.resize(sensor.depth.cloud.size);
  sensor.infra.data.Is.resize(sensor.depth.cloud.size);

  //---------------------------
}

}
