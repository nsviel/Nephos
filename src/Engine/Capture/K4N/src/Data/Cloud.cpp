#include "Cloud.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <execution>


namespace eng::k4n::data{

//Constructor / Destructor
Cloud::Cloud(eng::k4n::Node* node_k4n){
  //---------------------------

  this->engine = node_k4n->get_node_engine();
  this->k4n_operation = new eng::k4n::utils::Operation();
  this->ope_voxelizer = new eng::ope::Voxelizer();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::convert_into_cloud(eng::k4n::dev::Sensor* sensor){
  if(!sensor->depth.data_to_color.k4a_image.is_valid()) return;
  if(sensor->depth.data_to_color.k4a_image.get_width_pixels() != 1280) return;
  if(!sensor->ir.data.k4a_image.is_valid()) return;
  //---------------------------

  this->loop_init(sensor);
  this->loop_data(sensor);
  this->loop_end(sensor);

  //---------------------------
}

//Loop function
void Cloud::loop_init(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  vec_xyz.clear();
  vec_rgb.clear();
  vec_ir.clear();
  vec_r.clear();
  vec_goodness.clear();

  //---------------------------
}
void Cloud::loop_data(eng::k4n::dev::Sensor* sensor){
  prf::Tasker* profiler = sensor->tasker_cap;
  //---------------------------

  // Cloud stuff
  profiler->task_begin("cloud::transformation");
  k4a::image cloud_image;
  this->retrieve_cloud(sensor, cloud_image);
  int16_t* point_cloud_data = reinterpret_cast<int16_t*>(cloud_image.get_buffer());
  int point_cloud_size = cloud_image.get_size() / (3*sizeof(int16_t));
  profiler->task_end("cloud::transformation");

  vec_xyz.reserve(point_cloud_size);
  vec_rgb.reserve(point_cloud_size);
  vec_ir.reserve(point_cloud_size);
  vec_r.reserve(point_cloud_size);
  vec_goodness.reserve(point_cloud_size);

  profiler->task_begin("cloud::data");
  #pragma omp parallel for
  for(int i=0; i<point_cloud_size; i++){
    this->retrieve_location(sensor, i, point_cloud_data);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
    this->retrieve_goodness(i);
    this->insert_data(i);
  }
  profiler->task_end("cloud::data");

  //---------------------------
}
void Cloud::loop_end(eng::k4n::dev::Sensor* sensor){
  utl::type::Data* data = sensor->get_data();
  eng::k4n::dev::Master* master = sensor->master;
  prf::Tasker* profiler = sensor->tasker_cap;
  //---------------------------

  //profiler->task_begin("cloud::lock");
  //std::unique_lock<std::mutex> lock(data->mutex);
  //profiler->task_end("cloud::lock");

  //Cloud data copy
  //COPIER LES DONN2ES DIRECTEMENT
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
  /*
  profiler->task_begin("cloud::voxel");
  float voxel_size = master->voxel.voxel_size;
  int min_nb_point = master->voxel.min_nb_point;
  ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  ope_voxelizer->reconstruct_data_by_goodness(data);
  profiler->task_end("cloud::voxel");
  */

  //Update object data
  profiler->task_begin("cloud::update");
  utl::entity::Object* object = sensor->get_object();
  object->update_data();
  profiler->task_end("cloud::update");

  //---------------------------
}

//Data retrieval
void Cloud::retrieve_cloud(eng::k4n::dev::Sensor* sensor, k4a::image& cloud_image){
  eng::k4n::structure::Depth* depth = &sensor->depth;
  //---------------------------

  //Create cloud image
  cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->data_to_color.width, depth->data_to_color.height, depth->data_to_color.width * sizeof(int16_t) * 3);

  //Transform depth into cloud
  sensor->param.transformation.depth_image_to_point_cloud(depth->data_to_color.k4a_image, K4A_CALIBRATION_TYPE_COLOR, &cloud_image);

  //---------------------------
}
void Cloud::retrieve_location(eng::k4n::dev::Sensor* sensor, int i, int16_t* data){
  //---------------------------

  int depth_idx = i * 3;
  int x = data[depth_idx];
  int y = data[depth_idx+1];
  int z = data[depth_idx+2];

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
void Cloud::retrieve_color(eng::k4n::dev::Sensor* sensor, int i){
  eng::k4n::structure::Operation* operation = &sensor->master->operation;
  //---------------------------

  //Camera color
  if(operation->color_mode == 0){
    const uint8_t* color_data = sensor->color.data.buffer;

    int index = i * 4;
    float r = static_cast<float>(color_data[index + 2]) / 255.0f;
    float g = static_cast<float>(color_data[index + 1]) / 255.0f;
    float b = static_cast<float>(color_data[index + 0]) / 255.0f;
    float a = 1.0f;
    rgb = vec4(r, g, b, a);
  }
  //Else white
  else{
    rgb = vec4(1, 1, 1, 1);
  }

  //---------------------------
}
void Cloud::retrieve_ir(eng::k4n::dev::Sensor* sensor, int i){
  //---------------------------

  const uint8_t* ir_buffer = sensor->ir.data_to_color.buffer;

  int index = i * 2;
  ir = static_cast<uint16_t>(ir_buffer[index]) | (static_cast<uint16_t>(ir_buffer[index + 1]) << 8);

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

  if(1){//goodness == true){
    vec_xyz.push_back(xyz);
    vec_rgb.push_back(rgb);
    vec_ir.push_back(ir);
    vec_r.push_back(R);
    vec_goodness.push_back(goodness);
  }

  /*
  if(goodness == true){
    data->xyz.push_back(xyz);
    data->rgb.push_back(rgb);
    data->Is.push_back(ir);
    data->R.push_back(R);
    data->goodness.push_back(goodness);
  }
  */

  //---------------------------
}



}
