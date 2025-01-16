#include "Location.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::cloud{

//Constructor / Destructor
Location::Location(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->atr_field = new dat::atr::field::Manager();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Location::~Location(){}

//Main function
void Location::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->extraction_data(sensor);
  this->extraction_transfer(sensor);
  atr_location->compute_height(sensor);

  //---------------------------
}

//Subfunction
void Location::extraction_data(k4n::base::Sensor& sensor){
  const int16_t* buffer_depth = reinterpret_cast<int16_t*>(sensor.depth.cloud.buffer);
  //---------------------------

  sensor.depth.data.xyz.resize(sensor.depth.cloud.size);
  sensor.depth.data.R.resize(sensor.depth.cloud.size);

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor.depth.cloud.size; i++){
    //Raw values
    int idx = i * 3;
    float x = buffer_depth[idx + 0];
    float y = buffer_depth[idx + 1];
    float z = buffer_depth[idx + 2];

    //Convert coordinate in meter and X axis oriented.
    float x_m = -x / 1000.0f;
    float y_m = -y / 1000.0f;
    float z_m = z / 1000.0f;

    //Compute final values
    glm::vec3 xyz = glm::vec3(z_m, x_m, y_m);
    float R = math::distance_from_origin(xyz);

    //Store
    sensor.depth.data.xyz[i] = xyz;
    sensor.depth.data.R[i] = R;
  }

  //---------------------------
}
void Location::extraction_transfer(k4n::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data.mutex);

  data.xyz = sensor.depth.data.xyz;
  data.size = sensor.depth.cloud.size;
  data.width = sensor.depth.cloud.width;
  data.height = sensor.depth.cloud.height;

  std::vector<float>& vec_R = atr_field->get_field_data(data, "R");
  vec_R = sensor.depth.data.R;

  //---------------------------
}


}
