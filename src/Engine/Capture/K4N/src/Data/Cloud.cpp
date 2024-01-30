#include "Cloud.h"

#include <Engine/Node.h>
#include <Engine/Scene/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>


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
  //---------------------------

  this->loop_init(sensor);
  this->loop_data(sensor);
  this->loop_end(sensor);
  //this->retrieve_corner_coordinate(sensor);

  //---------------------------
}

//Loop function
void Cloud::loop_init(eng::k4n::dev::Sensor* sensor){
  if(sensor->depth.data.buffer.empty()) return;
  //---------------------------

  vec_xyz.clear();
  vec_rgb.clear();
  vec_ir.clear();
  vec_r.clear();
  vec_goodness.clear();

  //---------------------------
}
void Cloud::loop_data(eng::k4n::dev::Sensor* sensor){
  if(sensor->depth.data_to_color.buffer.empty()) return;
  if(sensor->depth.data_to_color.image.get_width_pixels() != 1280) return;
  //---------------------------

  // Cloud stuff
  eng::k4n::structure::Depth* depth = &sensor->depth;
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->data_to_color.width, depth->data_to_color.height, depth->data_to_color.width * sizeof(int16_t) * 3);
  sensor->param.transformation.depth_image_to_point_cloud(depth->data_to_color.image, K4A_CALIBRATION_TYPE_COLOR, &cloud_image);
  int16_t* point_cloud_data = reinterpret_cast<int16_t*>(cloud_image.get_buffer());

  // Convert point cloud data to vector<glm::vec3>
  for(int i=0; i<cloud_image.get_size()/(3*sizeof(int16_t)); i++){
    this->retrieve_location(sensor, i, point_cloud_data);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
    this->retrieve_goodness(i);
  }

  //---------------------------
}
void Cloud::loop_end(eng::k4n::dev::Sensor* sensor){
  if(sensor->depth.data.buffer.empty()) return;
  utl::type::Data* data = sensor->object->data;
  eng::k4n::dev::Master* master = sensor->master;
  //---------------------------

  std::unique_lock<std::mutex> lock(data->mutex);

  //Store capture data
  data->xyz = vec_xyz;
  data->Is = vec_ir;
  data->R = vec_r;
  data->goodness = vec_goodness;

  //Final colorization
  k4n_operation->make_colorization(sensor, vec_rgb);
  data->rgb = vec_rgb;

  //Voxelization filtering
  float voxel_size = master->voxel.voxel_size;
  int min_nb_point = master->voxel.min_nb_point;
  ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  ope_voxelizer->reconstruct_data_by_goodness(data);

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
  glm::vec3 point_m(z/1000.0f, -x/1000.0f, -y/1000.0f);
  vec_xyz.push_back(point_m);

  //Range calculation
  float R = sqrt(pow(point_m.x, 2) + pow(point_m.y, 2) + pow(point_m.z, 2));
  vec_r.push_back(R);

  //---------------------------
}
void Cloud::retrieve_color(eng::k4n::dev::Sensor* sensor, int i){
  //---------------------------

  eng::k4n::structure::Operation* operation = &sensor->master->operation;
  glm::vec4 color = vec4(1, 1, 1, 1);

  if(operation->color_mode == 0){
    //Camera color
    if(sensor->color.data.buffer.empty()) return;
    const vector<uint8_t>& color_data = sensor->color.data.buffer;

    int index = i * 4;
    float r = static_cast<float>(color_data[index + 2]) / 255.0f;
    float g = static_cast<float>(color_data[index + 1]) / 255.0f;
    float b = static_cast<float>(color_data[index + 0]) / 255.0f;
    float a = 1.0f;
    color = vec4(r, g, b, a);
  }

  //---------------------------
  vec_rgb.push_back(color);
}
void Cloud::retrieve_ir(eng::k4n::dev::Sensor* sensor, int i){
  if(sensor->ir.data.buffer.empty()) return;
  //---------------------------

  const vector<uint8_t>& ir_buffer = sensor->ir.data_to_color.buffer;

  int index = i * 2;
  uint16_t value = static_cast<uint16_t>(ir_buffer[index]) | (static_cast<uint16_t>(ir_buffer[index + 1]) << 8);

  //---------------------------
  vec_ir.push_back(value);
}
void Cloud::retrieve_goodness(int i){
  bool goodness = true;
  //---------------------------

  //location -> If null point set goodness to bad
  vec3 xyz = vec_xyz[i];
  if(xyz.x == 0 && xyz.y == 0 && xyz.z == 0){
    goodness = false;
  }

  //color -> If null color set goodness to bad
  //Maybe will be corrected with custom color to depth projection
  vec4 rgb = vec_rgb[i];
  if(rgb.x == 0 && rgb.y == 0 && rgb.z == 0){
    goodness = false;
  }

  //---------------------------
  vec_goodness.push_back(goodness);
}
void Cloud::retrieve_corner_coordinate(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  // Define your pixel coordinates and depth value
  int pixel_x = 640;  // replace ... with your pixel x-coordinate
  int pixel_y = 220;  // replace ... with your pixel y-coordinate
  float depth_value = 1749;  // replace ... with your depth value

  // Convert pixel coordinates and depth value to 3D coordinates
  k4a_float2_t pixel_point = { static_cast<float>(pixel_x), static_cast<float>(pixel_y) };
  k4a_float3_t xyz;
  int is_valid;
  k4a_calibration_2d_to_3d(&sensor->param.calibration, &pixel_point, depth_value, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &xyz, &is_valid);
  if(is_valid){
    glm::vec3 point(-xyz.v[2]/100.0f, -xyz.v[0]/100.0f, -xyz.v[1]/100.0f);
  }

  //---------------------------
}


}
