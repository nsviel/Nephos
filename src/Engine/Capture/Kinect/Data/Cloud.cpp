#include "Cloud.h"

#include <Engine/Engine.h>
#include <Engine/Data/Scene/Scene.h>


namespace eng::kinect::data{

//Constructor / Destructor
Cloud::Cloud(Engine* engine){
  //---------------------------

  this->engine = engine;

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::convert_into_cloud(K4A_device* k4a_device){
  //---------------------------

  this->retrieve_location(k4a_device);
  //this->retrieve_corner_coordinate(k4a_device);

  //---------------------------
}

//Subfunction
void Cloud::retrieve_location(K4A_device* k4a_device){
  if(k4a_device->color.image_depth.data.empty()) return;
  if(k4a_device->depth.image.data.empty()) return;
  //---------------------------

  // Depth stuff
  eng::kinect::structure::Depth* depth = &k4a_device->depth;
  vec_xyz.clear();

  // Color stuff
  vec_rgba.clear();

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
      //coordinate base 10m and oriented -X axis.
      glm::vec3 point(-z/100.0f, -x/100.0f, -y/100.0f);
      vec_xyz.push_back(point);

      this->retrieve_color(k4a_device, i);
    }
  }

  eng::kinect::structure::Cloud* cloud = k4a_device->get_cloud();
  cloud->object->xyz = vec_xyz;
  cloud->object->rgb = vec_rgba;

  //---------------------------
}
void Cloud::retrieve_color(K4A_device* k4a_device, int i){
  eng::kinect::structure::Cloud* cloud = k4a_device->get_cloud();
  glm::vec4 color;
  //---------------------------

  if(cloud->color_mode == 0){
    //Camera color
    const vector<uint8_t>& color_data = k4a_device->color.image_depth.data;

    int color_idx = i * 4;
    float r = static_cast<float>(color_data[color_idx + 2]) / 255.0f;
    float g = static_cast<float>(color_data[color_idx + 1]) / 255.0f;
    float b = static_cast<float>(color_data[color_idx])     / 255.0f;
    float a = 1.0f;
    color = vec4(r, g, b, a);
  }else if(cloud->color_mode == 1){
    //Colored unicolor
    color = cloud->object->unicolor;
  }else if(cloud->color_mode == 2){
    //White unicolor
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  }else if(cloud->color_mode == 3){
    //Heatmap
  }

  //---------------------------
  vec_rgba.push_back(color);
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
