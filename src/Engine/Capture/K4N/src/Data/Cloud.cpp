#include "Cloud.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


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
  utl::element::Profiler* profiler = sensor->cap_profiler;
  //---------------------------

  // Cloud stuff
  profiler->task_begin("cloud::transformation");
  eng::k4n::structure::Depth* depth = &sensor->depth;
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->data_to_color.width, depth->data_to_color.height, depth->data_to_color.width * sizeof(int16_t) * 3);
  sensor->param.transformation.depth_image_to_point_cloud(depth->data_to_color.k4a_image, K4A_CALIBRATION_TYPE_COLOR, &cloud_image);
  int16_t* point_cloud_data = reinterpret_cast<int16_t*>(cloud_image.get_buffer());
  profiler->task_end("cloud::transformation");

  // Convert point cloud data to vector<glm::vec3>
  profiler->task_begin("cloud::data");
  for(int i=0; i<cloud_image.get_size()/(3*sizeof(int16_t)); i++){
    this->retrieve_location(sensor, i, point_cloud_data);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
    this->retrieve_goodness(i);
    this->insert_data();
  }
  profiler->task_end("cloud::data");

  //---------------------------
}
void Cloud::loop_end(eng::k4n::dev::Sensor* sensor){
  utl::type::Data* data = sensor->object->data;
  eng::k4n::dev::Master* master = sensor->master;
  utl::element::Profiler* profiler = sensor->cap_profiler;
  //---------------------------

  profiler->task_begin("cloud::lock");
  std::unique_lock<std::mutex> lock(data->mutex);
  profiler->task_end("cloud::lock");

  //Store capture data
  data->xyz = vec_xyz;
  data->Is = vec_ir;
  data->R = vec_r;
  data->goodness = vec_goodness;
  data->nb_point = vec_xyz.size();

  //Final colorization
  profiler->task_begin("cloud::colorization");
  k4n_operation->make_colorization(sensor, vec_rgb);
  profiler->task_end("cloud::colorization");
  data->rgb = vec_rgb;

  //Voxelization filtering
  /*
  profiler->task_begin("cloud::voxel");
  float voxel_size = master->voxel.voxel_size;
  int min_nb_point = master->voxel.min_nb_point;
  ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  ope_voxelizer->reconstruct_data_by_goodness(data);
  profiler->task_end("cloud::voxel");
  */

  //Final small check
  if(data->xyz.size() != data->rgb.size()){
    cout<<"[error] cloud creation size problem"<<endl;
  }

  //---------------------------
}

//Subfunction
void Cloud::retrieve_location(eng::k4n::dev::Sensor* sensor, int i, int16_t* data){
  //---------------------------

  int depth_idx = i * 3;
  int x = data[depth_idx];
  int y = data[depth_idx+1];
  int z = data[depth_idx+2];

  //coordinate in meter and X axis oriented.
  xyz = vec3(z/1000.0f, -x/1000.0f, -y/1000.0f);

  //Range calculation
  R = sqrt(pow(xyz.x, 2) + pow(xyz.y, 2) + pow(xyz.z, 2));

  //---------------------------
}
void Cloud::retrieve_color(eng::k4n::dev::Sensor* sensor, int i){
  eng::k4n::structure::Operation* operation = &sensor->master->operation;
  //---------------------------

  //Camera color
  if(operation->color_mode == 0){
    const uint8_t* color_data = sensor->color.data.buffer_raw;

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

  const vector<uint8_t>& ir_buffer = sensor->ir.data_to_color.buffer_vec;

  int index = i * 2;
  ir = static_cast<uint16_t>(ir_buffer[index]) | (static_cast<uint16_t>(ir_buffer[index + 1]) << 8);

  //---------------------------
}
void Cloud::retrieve_goodness(int i){
  goodness = true;
  //---------------------------

  //location -> If null point set goodness to bad
  if(xyz.x == 0 && xyz.y == 0 && xyz.z == 0){
    goodness = false;
  }

  //color -> If null color set goodness to bad
  //Maybe will be corrected with custom color to depth projection
  if(rgb.x == 0 && rgb.y == 0 && rgb.z == 0){
    goodness = false;
  }

  //---------------------------
}
void Cloud::insert_data(){
  //---------------------------

  if(goodness == true){
    vec_xyz.push_back(xyz);
    vec_rgb.push_back(rgb);
    vec_ir.push_back(ir);
    vec_r.push_back(R);
    vec_goodness.push_back(goodness);
  }

  //---------------------------
}



}
