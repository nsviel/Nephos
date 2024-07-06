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

  //prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("cloud");
  //tasker->loop_begin();

  this->convertion_init(sensor);
  this->convertion_data(sensor);
  this->convertion_transfer(sensor);

  //tasker->loop_end();

  //---------------------------
}


void Data::convertion_init(k4n::structure::Sensor* sensor){
  //---------------------------

  //Depth transformation
  //tasker->task_begin("transformation");
  this->retrieve_cloud(sensor);
  //tasker->task_end("transformation");

  //Resize vectors
  //tasker->task_begin("reserve");
  int size = sensor->depth.cloud.size;
  vec_xyz.clear(); vec_xyz.reserve(size);
  vec_rgb.clear(); vec_rgb.reserve(size);
  vec_rgba.clear(); vec_rgba.reserve(size);
  vec_ir.clear(); vec_ir.reserve(size);
  vec_r.clear(); vec_r.reserve(size);
  //tasker->task_end("reserve");

  //---------------------------
}
void Data::convertion_data(k4n::structure::Sensor* sensor){
  //---------------------------

  //Fille vector with data
  //tasker->task_begin("data");
  #pragma omp parallel for
  for(int i=0; i<sensor->depth.cloud.size; i++){
    this->retrieve_location(sensor, i);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
    this->insert_data(i);
  }
  //tasker->task_end("data");

  //---------------------------
}
void Data::convertion_transfer(k4n::structure::Sensor* sensor){
  utl::base::Data* data = &sensor->data;
  dat::base::Set* master = sensor->set_parent;
  //---------------------------

  //Cloud data copy
  //tasker->task_begin("copying");
  data->xyz = vec_xyz;
  data->rgb = vec_rgb;
  data->Is = vec_ir;
  data->R = vec_r;

  data->size = vec_xyz.size();
  data->width = sensor->depth.cloud.width;
  data->height = sensor->depth.cloud.height;
  sensor->device.idx_cloud++;
  //tasker->task_end("copying");

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
  this->xyz = glm::vec3(z_m, x_m, y_m);

  //Range calculation
  this->R = math::distance_from_origin(xyz);

  //---------------------------
}
void Data::retrieve_color(k4n::structure::Sensor* sensor, int i){
  const uint8_t* buffer_color = sensor->color.cloud.buffer;
  //---------------------------

  int index = i * 4;
  float r = static_cast<float>(buffer_color[index + 2]) / 255.0f;
  float g = static_cast<float>(buffer_color[index + 1]) / 255.0f;
  float b = static_cast<float>(buffer_color[index + 0]) / 255.0f;
  this->rgb = glm::vec3(r, g, b);

  //---------------------------
}
void Data::retrieve_ir(k4n::structure::Sensor* sensor, int i){
  const int16_t* buffer_ir = reinterpret_cast<int16_t*>(sensor->ir.cloud.buffer);
  //---------------------------

  this->ir = buffer_ir[i];
  //vec3 Nxyz = sensor->buffer_Nxyz[i];
  //float It = math::compute_It(xyz, Nxyz, glm::vec3(0, 0, 0));
  //this->ir = rad_correction->apply_correction(I_raw, R, It);

  //---------------------------
}
void Data::insert_data(int i){
  //---------------------------

  vec_xyz.push_back(xyz);
  vec_rgb.push_back(rgb);
  vec_rgba.push_back(vec4(rgb.x, rgb.y, rgb.z, 1));
  vec_ir.push_back(ir);
  vec_r.push_back(R);

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
