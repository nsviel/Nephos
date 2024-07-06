#include "Data.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::processing::cloud{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::convert_image_into_cloud(k4n::structure::Sensor* sensor){
  if(check_condition(sensor) == false) return;
  //---------------------------

  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::cloud");

  tasker->loop();

  //init
  tasker->task_begin("init");
  this->convertion_init(sensor);
  tasker->task_end("init");

  //Extraction
  tasker->task_begin("extraction");
  this->convertion_data(sensor);
  tasker->task_end("extraction");

  //Transfer
  tasker->task_begin("transfer");
  this->convertion_transfer(sensor);
  tasker->task_end("transfer");

  //---------------------------
}


void Data::convertion_init(k4n::structure::Sensor* sensor){
  //---------------------------

  //Depth transformation
  this->retrieve_cloud(sensor);

  //Resize vectors
  int size = sensor->depth.cloud.size;
  buffer_data.xyz.clear(); buffer_data.xyz.reserve(size);
  buffer_data.rgb.clear(); buffer_data.rgb.reserve(size);
  buffer_data.rgba.clear(); buffer_data.rgba.reserve(size);
  buffer_data.Is.clear(); buffer_data.Is.reserve(size);
  buffer_data.R.clear(); buffer_data.R.reserve(size);

  //---------------------------
}
void Data::convertion_data(k4n::structure::Sensor* sensor){
  //---------------------------

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor->depth.cloud.size; i++){
    this->retrieve_location(sensor, i);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
  }

  //---------------------------
}
void Data::convertion_transfer(k4n::structure::Sensor* sensor){
  utl::base::Data* data = &sensor->data;
  dat::base::Set* master = sensor->set_parent;
  //---------------------------

  //Cloud data copy
  data->xyz = buffer_data.xyz;
  data->rgb = buffer_data.rgb;
  data->rgba = buffer_data.rgba;
  data->Is = buffer_data.Is;
  data->R = buffer_data.R;

  data->size = buffer_data.xyz.size();
  data->width = sensor->depth.cloud.width;
  data->height = sensor->depth.cloud.height;
  sensor->device.idx_cloud++;

  //---------------------------
}

//Data retrieval
void Data::retrieve_cloud(k4n::structure::Sensor* sensor){
  //---------------------------

  //Create cloud image
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, sensor->depth.cloud.width, sensor->depth.cloud.height, sensor->depth.cloud.width * sizeof(int16_t) * 3);

  //Transform depth into cloud
  sensor->device.transformation.depth_image_to_point_cloud(sensor->depth.cloud.k4a_image, sensor->depth.cloud.calibration_type, &cloud_image);
  sensor->depth.cloud.buffer = cloud_image.get_buffer();
  sensor->depth.cloud.size = cloud_image.get_size() / (3 * sizeof(int16_t));

  //---------------------------
}
void Data::retrieve_location(k4n::structure::Sensor* sensor, int i){
  const int16_t* buffer_depth = reinterpret_cast<int16_t*>(sensor->depth.cloud.buffer);
  //---------------------------

  int depth_idx = i * 3;
  double x = buffer_depth[depth_idx];
  double y = buffer_depth[depth_idx + 1];
  double z = buffer_depth[depth_idx + 2];

  //coordinate in meter and X axis oriented.
  double x_m = -x / 1000.0f;
  double y_m = -y / 1000.0f;
  double z_m = z / 1000.0f;
  glm::vec3 xyz = glm::vec3(z_m, x_m, y_m);
  float R = math::distance_from_origin(xyz);

  buffer_data.xyz.push_back(xyz);
  buffer_data.R.push_back(R);

  //---------------------------
}
void Data::retrieve_color(k4n::structure::Sensor* sensor, int i){
  const uint8_t* buffer_color = sensor->color.cloud.buffer;
  //---------------------------

  int index = i * 4;
  float r = static_cast<float>(buffer_color[index + 2]) / 255.0f;
  float g = static_cast<float>(buffer_color[index + 1]) / 255.0f;
  float b = static_cast<float>(buffer_color[index + 0]) / 255.0f;
  glm::vec3 rgb = glm::vec3(r, g, b);
  glm::vec4 rgba = glm::vec4(r, g, b, 1.0f);

  buffer_data.rgb.push_back(rgb);
  buffer_data.rgba.push_back(rgba);

  //---------------------------
}
void Data::retrieve_ir(k4n::structure::Sensor* sensor, int i){
  const int16_t* buffer_ir = reinterpret_cast<int16_t*>(sensor->ir.cloud.buffer);
  //---------------------------

  float ir = buffer_ir[i];
  //vec3 Nxyz = sensor->buffer_Nxyz[i];
  //float It = math::compute_It(xyz, Nxyz, glm::vec3(0, 0, 0));
  //this->ir = rad_correction->apply_correction(I_raw, R, It);

  buffer_data.Is.push_back(ir);

  //---------------------------
}
bool Data::check_condition(k4n::structure::Sensor* sensor){
  //---------------------------

  if(!sensor->depth.cloud.k4a_image.is_valid()) return false;
  if(!sensor->ir.cloud.k4a_image.is_valid()) return false;
  if(sensor->color.cloud.buffer == nullptr) return false;
  if(sensor->color.cloud.size != sensor->depth.cloud.size * 2) return false;

  //---------------------------
  return true;
}

}
