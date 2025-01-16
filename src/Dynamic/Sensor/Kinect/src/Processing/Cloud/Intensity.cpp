#include "Intensity.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::cloud{

//Constructor / Destructor
Intensity::Intensity(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->atr_field = new dat::atr::Field();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Intensity::~Intensity(){}

//Main function
void Intensity::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->extraction_data(sensor);
  this->extraction_transfer(sensor);

  //---------------------------
}

//Subfunction
void Intensity::extraction_data(k4n::base::Sensor& sensor){
  const int16_t* buffer_ir = reinterpret_cast<int16_t*>(sensor.infra.data.buffer);
  //---------------------------

  sensor.infra.data.Is.resize(sensor.depth.cloud.size);

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor.depth.cloud.size; i++){
    //Raw values
    float ir = buffer_ir[i];

    //Store
    sensor.infra.data.Is[i] = ir;
  }

  //---------------------------
}
void Intensity::extraction_transfer(k4n::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data.mutex);

  std::vector<float>& vec_I = atr_field->get_field_data(data, "I");
  vec_I = sensor.infra.data.Is;

  //---------------------------
}


}
