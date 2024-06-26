#include "Cloud.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>
#include <execution>


namespace k4n::processing{

//Constructor / Destructor
Cloud::Cloud(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dyn::Node* node_dynamic = node_engine->get_node_dynamic();

  this->thread_pool = node_engine->get_thread_pool();
  this->dyn_operation = node_dynamic->get_ope_cloud();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Cloud::run_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  //Convert data into a cloud
  this->convert_image_into_cloud(sensor);

  //Dynamic operation
  dyn_operation->start_thread(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Cloud::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  dyn_operation->wait_thread();

  //---------------------------
}

//Loop function
void Cloud::convert_image_into_cloud(k4n::structure::Sensor* sensor){
  if(!sensor->depth.cloud.k4a_image.is_valid()) return;
  if(!sensor->ir.cloud.k4a_image.is_valid()) return;
  if(sensor->color.cloud.buffer == nullptr) return;
  if(sensor->color.cloud.size != sensor->depth.cloud.size * 2) return;
  //---------------------------

  prf::graph::Tasker* tasker = sensor->profiler.fetch_tasker("cloud");
  tasker->loop_begin();

  this->convertion_init(sensor, tasker);
  this->convertion_data(sensor, tasker);
  this->convertion_transfer(sensor, tasker);

  tasker->loop_end();

  //---------------------------
}
void Cloud::convertion_init(k4n::structure::Sensor* sensor, prf::graph::Tasker* tasker){
  //---------------------------

  //Depth transformation
  tasker->task_begin("transformation");
  this->retrieve_cloud(sensor);
  tasker->task_end("transformation");

  //Resize vectors
  tasker->task_begin("reserve");
  int size = sensor->depth.cloud.size;
  vec_xyz.clear(); vec_xyz.reserve(size);
  vec_rgb.clear(); vec_rgb.reserve(size);
  vec_rgba.clear(); vec_rgba.reserve(size);
  vec_ir.clear(); vec_ir.reserve(size);
  vec_r.clear(); vec_r.reserve(size);
  tasker->task_end("reserve");

  //---------------------------
}
void Cloud::convertion_data(k4n::structure::Sensor* sensor, prf::graph::Tasker* tasker){
  //---------------------------

  //Fille vector with data
  tasker->task_begin("data");
  #pragma omp parallel for
  for(int i=0; i<sensor->depth.cloud.size; i++){
    this->retrieve_location(sensor, i);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
    this->insert_data(i);
  }
  tasker->task_end("data");

  //---------------------------
}
void Cloud::convertion_transfer(k4n::structure::Sensor* sensor, prf::graph::Tasker* tasker){
  utl::base::Data* data = &sensor->data;
  dat::base::Set* master = sensor->set_parent;
  //---------------------------

  //Cloud data copy
  tasker->task_begin("copying");
  data->xyz = vec_xyz;
  data->rgb = vec_rgb;
  data->Is = vec_ir;
  data->R = vec_r;

  data->size = vec_xyz.size();
  data->width = sensor->depth.cloud.width;
  data->height = sensor->depth.cloud.height;
  sensor->device.idx_cloud++;
  tasker->task_end("copying");

  //---------------------------
}

//Data retrieval
void Cloud::retrieve_cloud(k4n::structure::Sensor* sensor){
  //---------------------------

  //Create cloud image
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, sensor->depth.cloud.width, sensor->depth.cloud.height, sensor->depth.cloud.width * sizeof(int16_t) * 3);

  //Transform depth into cloud
  sensor->device.transformation.depth_image_to_point_cloud(sensor->depth.cloud.k4a_image, sensor->depth.cloud.calibration_type, &cloud_image);
  sensor->depth.cloud.buffer = cloud_image.get_buffer();
  sensor->depth.cloud.size = cloud_image.get_size() / (3 * sizeof(int16_t));

  //---------------------------
}
void Cloud::retrieve_location(k4n::structure::Sensor* sensor, int i){
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
  this->xyz = vec3(z_m, x_m, y_m);

  //Range calculation
  this->R = math::distance_from_origin(xyz);

  //---------------------------
}
void Cloud::retrieve_color(k4n::structure::Sensor* sensor, int i){
  const uint8_t* buffer_color = sensor->color.cloud.buffer;
  //---------------------------

  int index = i * 4;
  float r = static_cast<float>(buffer_color[index + 2]) / 255.0f;
  float g = static_cast<float>(buffer_color[index + 1]) / 255.0f;
  float b = static_cast<float>(buffer_color[index + 0]) / 255.0f;
  this->rgb = glm::vec3(r, g, b);

  //---------------------------
}
void Cloud::retrieve_ir(k4n::structure::Sensor* sensor, int i){
  const int16_t* buffer_ir = reinterpret_cast<int16_t*>(sensor->ir.cloud.buffer);
  //---------------------------

  this->ir = buffer_ir[i];
  //vec3 Nxyz = sensor->buffer_Nxyz[i];
  //float It = math::compute_It(xyz, Nxyz, glm::vec3(0, 0, 0));
  //this->ir = rad_correction->apply_correction(I_raw, R, It);

  //---------------------------
}
void Cloud::insert_data(int i){
  //---------------------------

  vec_xyz.push_back(xyz);
  vec_rgb.push_back(rgb);
  vec_rgba.push_back(vec4(rgb.x, rgb.y, rgb.z, 1));
  vec_ir.push_back(ir);
  vec_r.push_back(R);

  //---------------------------
}

}