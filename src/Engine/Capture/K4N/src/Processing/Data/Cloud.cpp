#include "Cloud.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <execution>


namespace k4n::processing{

//Constructor / Destructor
Cloud::Cloud(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_operation = new k4n::utils::Operation();
  this->k4n_processing = new k4n::processing::Operation(node_k4n);
  this->k4n_calibration = new k4n::processing::Calibration(node_k4n);
  this->k4n_pool = node_k4n->get_k4n_pool();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  k4n_pool->add_task(task_function);

  //---------------------------
}
void Cloud::run_thread(k4n::dev::Sensor* sensor){
  if(sensor->profiler == nullptr) return;
  //---------------------------

  //Convert data into a cloud
  this->convert_into_cloud(sensor);

  //Update object data
  k4n_processing->start_thread(sensor);

  //Update object data
  k4n_calibration->start_thread(sensor);

  //---------------------------
  this->idle = true;
}
void Cloud::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_processing->wait_thread();

  //---------------------------
}

//Cloud function
void Cloud::convert_into_cloud(k4n::dev::Sensor* sensor){
  if(!sensor->depth.cloud.k4a_image.is_valid()) return;
  if(!sensor->ir.cloud.k4a_image.is_valid()) return;
  if(sensor->color.cloud.buffer == nullptr) return;
  if(sensor->color.cloud.size != sensor->depth.cloud.size * 2) return;
  //---------------------------

  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("cloud");
  tasker->loop_begin();

  this->loop_init(sensor);
  this->loop_data(sensor, tasker);
  this->loop_end(sensor, tasker);

  tasker->loop_end();

  //---------------------------
}
void Cloud::loop_init(k4n::dev::Sensor* sensor){
  //---------------------------

  vec_xyz.clear();
  vec_rgb.clear();
  vec_ir.clear();
  vec_r.clear();
  vec_goodness.clear();

  //---------------------------
}
void Cloud::loop_data(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker){
  //---------------------------

  //Color
  k4a::image image_color = sensor->color.cloud.k4a_image;
  const uint8_t* buffer_color = sensor->color.cloud.buffer;

  //Infrared
  k4a::image image_ir = sensor->ir.cloud.k4a_image;
  const uint8_t* buffer_ir = sensor->ir.cloud.buffer;

  //Cloud XYZ
  tasker->task_begin("transformation");
  k4a::image cloud_image;
  this->retrieve_cloud(sensor, cloud_image);
  const int16_t* data_xyz = reinterpret_cast<int16_t*>(cloud_image.get_buffer());
  this->point_cloud_size = cloud_image.get_size() / (3*sizeof(int16_t));
  tasker->task_end("transformation");

  tasker->task_begin("reserve");
  vec_xyz.reserve(point_cloud_size);
  vec_rgb.reserve(point_cloud_size);
  vec_ir.reserve(point_cloud_size);
  vec_r.reserve(point_cloud_size);
  vec_goodness.reserve(point_cloud_size);
  tasker->task_end("reserve");

  tasker->task_begin("data");
  #pragma omp parallel for
  for(int i=0; i<point_cloud_size; i++){
    this->retrieve_location(i, data_xyz);
    this->retrieve_color(i, buffer_color);
    this->retrieve_ir(i, buffer_ir);
    this->retrieve_goodness(i);
    this->insert_data(i);
  }
  tasker->task_end("data");

  //---------------------------
}
void Cloud::loop_end(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker){
  utl::type::Data* data = sensor->get_data();
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Cloud data copy
  tasker->task_begin("copying");
  data->xyz = vec_xyz;
  data->rgb = vec_rgb;
  data->Is = vec_ir;
  data->R = vec_r;
  data->goodness = vec_goodness;
  data->size = vec_xyz.size();
  data->width = sensor->depth.cloud.width;
  data->height = sensor->depth.cloud.height;
  sensor->param.index_cloud++;
  tasker->task_end("copying");

  //---------------------------
}

//Data retrieval
void Cloud::retrieve_cloud(k4n::dev::Sensor* sensor, k4a::image& cloud_image){
  k4n::structure::Depth* depth = &sensor->depth;
  //---------------------------

  //Create cloud image
  cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->cloud.width, depth->cloud.height, depth->cloud.width * sizeof(int16_t) * 3);

  //Transform depth into cloud
  sensor->param.transformation.depth_image_to_point_cloud(depth->cloud.k4a_image, depth->cloud.calibration_type, &cloud_image);

  //---------------------------
}
void Cloud::retrieve_location(int i, const int16_t* data_xyz){
  //---------------------------

  int depth_idx = i * 3;
  int x = data_xyz[depth_idx];
  int y = data_xyz[depth_idx + 1];
  int z = data_xyz[depth_idx + 2];

  //coordinate in meter and X axis oriented.
  float inv_scale = 1.0f / 1000.0f;
  float x_m = -x * inv_scale;
  float y_m = -y * inv_scale;
  float z_m = z * inv_scale;
  xyz = vec3(z_m, x_m, y_m);

  //Range calculation
  R = x_m * x_m + y_m * y_m + z_m * z_m;

  //---------------------------
}
void Cloud::retrieve_color(int i, const uint8_t* data_rgb){
  if(data_rgb == nullptr) return;
  //---------------------------

  int index = i * 4;
  float r = static_cast<float>(data_rgb[index + 2]) / 255.0f;
  float g = static_cast<float>(data_rgb[index + 1]) / 255.0f;
  float b = static_cast<float>(data_rgb[index + 0]) / 255.0f;
  float a = 1.0f;
  rgb = vec4(r, g, b, a);

  //---------------------------
}
void Cloud::retrieve_ir(int i, const uint8_t* data_ir){
  //---------------------------

  int index = i * 2;
  ir = static_cast<uint16_t>(data_ir[index]) | (static_cast<uint16_t>(data_ir[index + 1]) << 8);

  //---------------------------
}
void Cloud::retrieve_goodness(int i){
  //---------------------------

  // Location -> If null point set goodness to bad
  // Color -> If null color set goodness to bad
  //goodness = !(xyz.x == 0 && xyz.y == 0 && xyz.z == 0) && !(rgb.x == 0 && rgb.y == 0 && rgb.z == 0);


  //---------------------------
}
void Cloud::insert_data(int i){
  //---------------------------

  vec_xyz.push_back(xyz);
  vec_rgb.push_back(rgb);
  vec_ir.push_back(ir);
  vec_r.push_back(R);
  vec_goodness.push_back(goodness);

  //---------------------------
}

}