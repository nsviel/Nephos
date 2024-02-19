#include "Cloud.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <execution>


namespace k4n::data{

//Constructor / Destructor
Cloud::Cloud(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_operation = new k4n::utils::Operation();
  //this->ope_voxelizer = new eng::ope::Voxelizer();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::convert_into_cloud(k4n::dev::Sensor* sensor){
  if(!sensor->depth.cloud.k4a_image.is_valid()) return;
  if(sensor->depth.cloud.k4a_image.get_width_pixels() < 1000) return;
  if(!sensor->ir.data.k4a_image.is_valid()) return;
  //---------------------------

  this->loop_init(sensor);
  this->loop_data(sensor);
  this->loop_end(sensor);

  //---------------------------
}

//Loop function
void Cloud::loop_init(k4n::dev::Sensor* sensor){
  //---------------------------

  vec_xyz.clear();
  vec_rgb.clear();
  vec_ir.clear();
  vec_r.clear();
  vec_goodness.clear();

  //---------------------------
}
void Cloud::loop_data(k4n::dev::Sensor* sensor){
  prf::Tasker* profiler = sensor->tasker_cap;
  //---------------------------

  // Cloud stuff
  profiler->task_begin("cloud::transformation");
  k4a::image cloud_image;
  this->retrieve_cloud(sensor, cloud_image);
  const int16_t* data_xyz = reinterpret_cast<int16_t*>(cloud_image.get_buffer());
  this->point_cloud_size = cloud_image.get_size() / (3*sizeof(int16_t));
  profiler->task_end("cloud::transformation");

  vec_xyz = vector<vec3>(point_cloud_size);
  vec_rgb = vector<vec4>(point_cloud_size);
  vec_ir = vector<float>(point_cloud_size);
  vec_r = vector<float>(point_cloud_size);
  vec_goodness = vector<bool>(point_cloud_size);

  const uint8_t* data_rgb = sensor->color.cloud.buffer;
  const uint8_t* data_ir = sensor->ir.cloud.buffer;

  profiler->task_begin("cloud::data");
  #pragma omp parallel for
  for(int i=0; i<point_cloud_size; i++){
    this->retrieve_location(i, data_xyz);
    this->retrieve_color(i, data_rgb);
    this->retrieve_ir(i, data_ir);
    this->retrieve_goodness(i);
    this->insert_data(i);
  }
  profiler->task_end("cloud::data");

  //---------------------------
}
void Cloud::loop_end(k4n::dev::Sensor* sensor){
  utl::type::Data* data = sensor->get_data();
  k4n::dev::Master* master = sensor->master;
  prf::Tasker* profiler = sensor->tasker_cap;
  //---------------------------

  //Cloud data copy
  profiler->task_begin("cloud::copying");
  data->xyz = vec_xyz;
  data->Is = vec_ir;
  data->R = vec_r;
  data->goodness = vec_goodness;
  data->nb_point = vec_xyz.size();
  profiler->task_end("cloud::copying");

  //Final colorization
  profiler->task_begin("cloud::colorization");
  k4n_operation->make_colorization(sensor, vec_rgb);
  data->rgb = vec_rgb;
  profiler->task_end("cloud::colorization");

  //Voxelization filtering
  //profiler->task_begin("cloud::voxel");
  //float voxel_size = master->voxel.voxel_size;
  //int min_nb_point = master->voxel.min_nb_point;
  //ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  //ope_voxelizer->reconstruct_data_by_goodness(data);
  //profiler->task_end("cloud::voxel");

  //Update object data
  profiler->task_begin("cloud::update");
  utl::entity::Object* object = sensor->get_object();
  object->update_data();
  profiler->task_end("cloud::update");

  //---------------------------
}

//Data retrieval
void Cloud::retrieve_cloud(k4n::dev::Sensor* sensor, k4a::image& cloud_image){
  k4n::structure::Depth* depth = &sensor->depth;
  //---------------------------

  //Create cloud image
  cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->cloud.width, depth->cloud.height, depth->cloud.width * sizeof(int16_t) * 3);

  //Transform depth into cloud
  sensor->param.transformation.depth_image_to_point_cloud(depth->cloud.k4a_image, K4A_CALIBRATION_TYPE_COLOR, &cloud_image);

  //---------------------------
}
void Cloud::retrieve_location(int i, const int16_t* data_xyz){
  //---------------------------

  int depth_idx = i * 3;
  int x = data_xyz[depth_idx];
  int y = data_xyz[depth_idx+1];
  int z = data_xyz[depth_idx+2];

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

  vec_xyz[i] = xyz;
  vec_rgb[i] = rgb;
  vec_ir[i] = ir;
  vec_r[i] = R;
  vec_goodness[i] = goodness;

  //---------------------------
}



}
