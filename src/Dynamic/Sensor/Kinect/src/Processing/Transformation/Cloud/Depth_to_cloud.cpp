#include "Depth_to_cloud.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::transformation{

//Constructor / Destructor
Depth_to_cloud::Depth_to_cloud(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Depth_to_cloud::~Depth_to_cloud(){}

//Main function
void Depth_to_cloud::make_transformation(k4n::base::Sensor& sensor){
  if(!sensor.depth.data.image.is_valid()) return;
  //---------------------------

  this->create_cloud_image(sensor);
  this->transform_to_cloud(sensor);

  //---------------------------
}

//Subfunction
void Depth_to_cloud::create_cloud_image(k4n::base::Sensor& sensor){
  //---------------------------

  //Create cloud image
  sensor.depth.cloud.image = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM,
    sensor.depth.data.width,
    sensor.depth.data.height,
    sensor.depth.data.width * sizeof(int16_t) * 3
  );

  //---------------------------
}
void Depth_to_cloud::transform_to_cloud(k4n::base::Sensor& sensor){
  //---------------------------

  sensor.device.transformation.depth_image_to_point_cloud(sensor.depth.data.image, sensor.device.calibration_type, &sensor.depth.cloud.image);
  sensor.depth.cloud.buffer = sensor.depth.cloud.image.get_buffer();
  sensor.depth.cloud.size = sensor.depth.cloud.image.get_size() / (3 * sizeof(int16_t));

  //---------------------------
}

}
