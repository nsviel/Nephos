#include "Cloud.h"

#include <Engine/Engine.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Operation/src/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace eng::k4n::data{

//Constructor / Destructor
Cloud::Cloud(eng::k4n::Node* k4n_node){
  //---------------------------

  this->engine = k4n_node->get_engine();
  this->k4n_operation = new eng::k4n::utils::Operation();
  this->ope_voxelizer = new eng::ope::Voxelizer();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::convert_into_cloud(eng::k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  this->loop_init(k4n_sensor);
  this->loop_data(k4n_sensor);
  this->loop_end(k4n_sensor);
  //this->retrieve_corner_coordinate(k4n_sensor);

  //---------------------------
}

//Loop function
void Cloud::loop_init(eng::k4n::dev::Sensor* k4n_sensor){
  if(k4n_sensor->depth.image.data.empty()) return;
  //---------------------------

  vec_xyz.clear();
  vec_rgba.clear();
  vec_ir.clear();
  vec_r.clear();
  vec_idx.clear();

  //---------------------------
}
void Cloud::loop_data(eng::k4n::dev::Sensor* k4n_sensor){
  if(k4n_sensor->depth.image.data.empty()) return;
  //---------------------------

  // Data stuff
  eng::k4n::structure::Depth* depth = &k4n_sensor->depth;
  eng::k4n::structure::Infrared* ir = &k4n_sensor->ir;

  // Cloud stuff
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->image.width, depth->image.height, depth->image.width * 3 * (int)sizeof(int16_t));
  k4n_sensor->param.transformation.depth_image_to_point_cloud(depth->image.image, K4A_CALIBRATION_TYPE_DEPTH, &cloud_image);
  int16_t* point_cloud_data = reinterpret_cast<int16_t*>(cloud_image.get_buffer());

  // Convert point cloud data to vector<glm::vec3>
  for(int i=0; i<cloud_image.get_size()/(3*sizeof(int16_t)); i++){
    this->retrieve_location(k4n_sensor, i, point_cloud_data);
    this->retrieve_color(k4n_sensor, i);
    this->retrieve_ir(k4n_sensor, i);
  }

  //---------------------------
}
void Cloud::loop_end(eng::k4n::dev::Sensor* k4n_sensor){
  if(k4n_sensor->depth.image.data.empty()) return;
  utl::type::Data* data = k4n_sensor->object->data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data->mutex);

  //Store capture data
  data->nb_point = vec_xyz.size();
  data->xyz = vec_xyz;
  data->Is = vec_ir;
  data->R = vec_r;
  data->idx = vec_idx;

  //Final colorization
  k4n_operation->make_colorization(k4n_sensor, vec_rgba);
  data->rgb = vec_rgba;

  //Voxelization filtering
  ope_voxelizer->find_voxel_min_number_of_point(data);
  ope_voxelizer->reconstruct_data_by_goodness(data);

  //Final small check
  if(data->xyz.size() != data->rgb.size()){
    cout<<"[error] cloud creation size problem"<<endl;
  }

  //---------------------------
}

//Subfunction
void Cloud::retrieve_location(eng::k4n::dev::Sensor* k4n_sensor, int i, int16_t* data){
  //---------------------------

  int depth_idx = i * 3;
  int x = data[depth_idx];
  int y = data[depth_idx+1];
  int z = data[depth_idx+2];

  //coordinate in meter and X axis oriented.
  glm::vec3 point_m(z/1000.0f, -x/1000.0f, -y/1000.0f);
  vec_xyz.push_back(point_m);

  //Range calculation
  float R = sqrt(pow(point_m.x, 2) + pow(point_m.y, 2) + pow(point_m.z, 2));
  vec_r.push_back(R);

  //If null point set goodness to bad
  if(x != 0 && y != 0 && z != 0){
    vec_idx.push_back(true);
  }else{
    vec_idx.push_back(false);
  }

  //---------------------------
}
void Cloud::retrieve_color(eng::k4n::dev::Sensor* k4n_sensor, int i){
  //---------------------------

  eng::k4n::structure::Operation* operation = &k4n_sensor->master->operation;
  glm::vec4 color;

  if(operation->color_mode == 0){
    //Camera color
    if(k4n_sensor->color.image_depth.data.empty()) return;
    const vector<uint8_t>& color_data = k4n_sensor->color.image_depth.data;

    int color_idx = i * 4;
    float r = static_cast<float>(color_data[color_idx + 0]) / 255.0f;
    float g = static_cast<float>(color_data[color_idx + 1]) / 255.0f;
    float b = static_cast<float>(color_data[color_idx + 2]) / 255.0f;
    float a = 1.0f;
    color = vec4(r, g, b, a);
  }

  //---------------------------
  vec_rgba.push_back(color);
}
void Cloud::retrieve_ir(eng::k4n::dev::Sensor* k4n_sensor, int i){
  if(k4n_sensor->ir.image.data.empty()) return;
  //---------------------------

  const vector<uint8_t>& ir_data = k4n_sensor->ir.image.data;

  int color_idx = i * 2;
  uint16_t value = static_cast<uint16_t>(ir_data[color_idx]) | (static_cast<uint16_t>(ir_data[color_idx + 1]) << 8);

  //---------------------------
  vec_ir.push_back(value);
}
void Cloud::retrieve_corner_coordinate(eng::k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  // Define your pixel coordinates and depth value
  int pixel_x = 640;  // replace ... with your pixel x-coordinate
  int pixel_y = 220;  // replace ... with your pixel y-coordinate
  float depth_value = 1749;  // replace ... with your depth value

  // Convert pixel coordinates and depth value to 3D coordinates
  k4a_float2_t pixel_point = { static_cast<float>(pixel_x), static_cast<float>(pixel_y) };
  k4a_float3_t xyz;
  int is_valid;
  k4a_calibration_2d_to_3d(&k4n_sensor->param.calibration, &pixel_point, depth_value, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &xyz, &is_valid);
  if(is_valid){
    glm::vec3 point(-xyz.v[2]/100.0f, -xyz.v[0]/100.0f, -xyz.v[1]/100.0f);
  }

  //---------------------------
}


}
