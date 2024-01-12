#include "Cloud.h"

#include <Engine/Engine.h>
#include <Engine/Scene/Data/Scene.h>
#include <Engine/Operation/Transformation/Transformation.h>


namespace k4a::data{

//Constructor / Destructor
Cloud::Cloud(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->kin_operation = new k4a::utils::Operation();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::convert_into_cloud(K4A_device* k4a_device){
  //---------------------------

  this->loop_init(k4a_device);
  this->loop_data(k4a_device);
  this->loop_end(k4a_device);
  //this->retrieve_corner_coordinate(k4a_device);

  //---------------------------
}

//Loop function
void Cloud::loop_init(K4A_device* k4a_device){
  if(k4a_device->depth.image.data.empty()) return;
  //---------------------------

  vec_xyz.clear();
  vec_rgba.clear();
  vec_ir.clear();
  vec_r.clear();

  //---------------------------
}
void Cloud::loop_data(K4A_device* k4a_device){
  if(k4a_device->depth.image.data.empty()) return;
  //---------------------------

  // Data stuff
  k4a::stucture::Depth* depth = &k4a_device->depth;
  k4a::stucture::Infrared* ir = &k4a_device->ir;

  // Cloud stuff
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->image.width, depth->image.height, depth->image.width * 3 * (int)sizeof(int16_t));
  k4a_device->device.transformation.depth_image_to_point_cloud(depth->image.image, K4A_CALIBRATION_TYPE_DEPTH, &cloud_image);
  int16_t* point_cloud_data = reinterpret_cast<int16_t*>(cloud_image.get_buffer());

  // Convert point cloud data to vector<glm::vec3>
  for(int i=0; i<cloud_image.get_size()/(3*sizeof(int16_t)); i++){
    int depth_idx = i * 3;
    int x = point_cloud_data[depth_idx];
    int y = point_cloud_data[depth_idx+1];
    int z = point_cloud_data[depth_idx+2];

    if(x != 0 && y != 0 && z != 0){
      this->retrieve_location(x, y, z);
      this->retrieve_color(k4a_device, i);
      this->retrieve_ir(k4a_device, i);
    }
  }

  //---------------------------
}
void Cloud::loop_end(K4A_device* k4a_device){
  if(k4a_device->depth.image.data.empty()) return;
  //---------------------------

  k4a::stucture::Cloud* cloud = k4a_device->get_cloud();
  std::unique_lock<std::mutex> lock(cloud->object->mutex);

  //Store capture data
  cloud->nb_point = vec_xyz.size();
  cloud->object->xyz = vec_xyz;
  cloud->object->Is = vec_ir;
  cloud->object->R = vec_r;

  //Final colorization
  kin_operation->make_colorization(cloud, vec_rgba);
  cloud->object->rgb = vec_rgba;

  if(cloud->object->xyz.size() != cloud->object->rgb.size()){
    cout<<"[error] cloud creation size problem"<<endl;
  }

  //---------------------------
}

//Subfunction
void Cloud::retrieve_location(int& x, int& y, int& z){
  //---------------------------

  //coordinate in meter and X axis oriented.
  glm::vec3 point_m(z/1000.0f, -x/1000.0f, -y/1000.0f);
  vec_xyz.push_back(point_m);

  //Range calculation
  float R = sqrt(pow(point_m.x, 2) + pow(point_m.y, 2) + pow(point_m.z, 2));
  vec_r.push_back(R);

  //---------------------------
}
void Cloud::retrieve_color(K4A_device* k4a_device, int i){
  //---------------------------

  k4a::stucture::Cloud* cloud = k4a_device->get_cloud();
  glm::vec4 color;

  if(cloud->color_mode == 0){
    //Camera color
    if(k4a_device->color.image_depth.data.empty()) return;
    const vector<uint8_t>& color_data = k4a_device->color.image_depth.data;

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
void Cloud::retrieve_ir(K4A_device* k4a_device, int i){
  if(k4a_device->ir.image.data.empty()) return;
  //---------------------------

  const vector<uint8_t>& ir_data = k4a_device->ir.image.data;

  int color_idx = i * 2;
  uint16_t value = static_cast<uint16_t>(ir_data[color_idx]) | (static_cast<uint16_t>(ir_data[color_idx + 1]) << 8);

  //---------------------------
  vec_ir.push_back(value);
}
void Cloud::retrieve_corner_coordinate(K4A_device* k4a_device){
  //---------------------------

  // Define your pixel coordinates and depth value
  int pixel_x = 640;  // replace ... with your pixel x-coordinate
  int pixel_y = 220;  // replace ... with your pixel y-coordinate
  float depth_value = 1749;  // replace ... with your depth value

  // Convert pixel coordinates and depth value to 3D coordinates
  k4a_float2_t pixel_point = { static_cast<float>(pixel_x), static_cast<float>(pixel_y) };
  k4a_float3_t xyz;
  int is_valid;
  k4a_calibration_2d_to_3d(&k4a_device->device.calibration, &pixel_point, depth_value, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &xyz, &is_valid);
  if(is_valid){
    glm::vec3 point(-xyz.v[2]/100.0f, -xyz.v[0]/100.0f, -xyz.v[1]/100.0f);
  }

  //---------------------------
}


}
