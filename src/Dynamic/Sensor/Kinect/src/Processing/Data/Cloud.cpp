#include "Cloud.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Cloud::Cloud(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_color = new k4n::cloud::Color(node_k4n);
  this->k4n_intensity = new k4n::cloud::Intensity(node_k4n);
  this->k4n_location = new k4n::cloud::Location(node_k4n);
  this->atr_field = new dat::atr::Field();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::extract_data(dat::base::Sensor& sensor){
  k4n::base::Sensor* k4n_sensor = dynamic_cast<k4n::base::Sensor*>(&sensor);
  if(check_condition(*k4n_sensor) == false) return;
  //---------------------------

  prf::monitor::Tasker* tasker = k4n_sensor->profiler.fetch_tasker("cloud");
  tasker->loop();

  //init
  tasker->task_begin("init");
  this->extraction_init(*k4n_sensor);
  tasker->task_end("init");

  //Extraction
  tasker->task_begin("extraction");
  k4n_color->extract_data(*k4n_sensor);
  k4n_intensity->extract_data(*k4n_sensor);
  k4n_location->extract_data(*k4n_sensor);
  tasker->task_end("extraction");

  //Transfer
  tasker->task_begin("transfer");
  this->extraction_transfer(*k4n_sensor);
  tasker->task_end("transfer");

  atr_location->compute_height(*k4n_sensor);

  //---------------------------
}

//Subfunction
bool Cloud::check_condition(k4n::base::Sensor& sensor){
  //---------------------------

  if(!sensor.depth.data.image.is_valid()) return false;
  if(!sensor.infra.data.image.is_valid()) return false;
  if(sensor.color.data.buffer == nullptr) return false;
  if(sensor.color.data.size != sensor.depth.data.size * 2) return false;

  //---------------------------
  return true;
}
void Cloud::extraction_init(k4n::base::Sensor& sensor){
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
void Cloud::extraction_transfer(k4n::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data.mutex);

  //Info
  data.size = sensor.depth.cloud.size;
  data.width = sensor.depth.cloud.width;
  data.height = sensor.depth.cloud.height;

  //---------------------------
}

}
