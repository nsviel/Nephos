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
  this->extraction_data(*k4n_sensor);
  tasker->task_end("extraction");

  k4n_color->extract_data(*k4n_sensor);
  k4n_intensity->extract_data(*k4n_sensor);
  k4n_location->extract_data(*k4n_sensor);

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
void Cloud::extraction_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor.depth.cloud.size; i++){
    this->retrieve_location(sensor, i);
    this->retrieve_ir(sensor, i);
  }

  //---------------------------
}
void Cloud::extraction_transfer(k4n::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data.mutex);

  std::unique_ptr<std::vector<float>> vec_I_ptr = atr_field->get_field_data(data, "I");
  std::unique_ptr<std::vector<float>> vec_R_ptr = atr_field->get_field_data(data, "R");
  if (!vec_I_ptr || !vec_R_ptr) return;

  std::vector<float>& vec_I = *vec_I_ptr;
  std::vector<float>& vec_R = *vec_R_ptr;

  //Data
  data.xyz = sensor.depth.data.xyz;
  data.rgb = sensor.color.data.rgb;
  data.rgba = sensor.color.data.rgba;
  vec_I = sensor.infra.data.Is;
  vec_R = sensor.depth.data.R;

  //Info
  data.size = sensor.depth.cloud.size;
  data.width = sensor.depth.cloud.width;
  data.height = sensor.depth.cloud.height;

  //---------------------------
}

//Data function
void Cloud::retrieve_location(k4n::base::Sensor& sensor, int i){
  const int16_t* buffer_depth = reinterpret_cast<int16_t*>(sensor.depth.cloud.buffer);
  //---------------------------

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

  //---------------------------
}
void Cloud::retrieve_ir(k4n::base::Sensor& sensor, int i){
  const int16_t* buffer_ir = reinterpret_cast<int16_t*>(sensor.infra.data.buffer);
  //---------------------------

  //Raw values
  float ir = buffer_ir[i];

  //Store
  sensor.infra.data.Is[i] = ir;

  //---------------------------
}

}
