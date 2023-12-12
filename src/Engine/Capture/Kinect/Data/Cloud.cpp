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
  this->retrieve_color(k4a_device);

  //---------------------------
}

//Subfunction
void Cloud::retrieve_location(K4A_device* k4a_device){
  //---------------------------

  // Depth stuff
  eng::kinect::structure::Depth* depth = &k4a_device->depth;
  std::vector<glm::vec3> vec_xyz;

  // Color stuff
  eng::kinect::structure::Color* color = &k4a_device->color;
  uint8_t* color_data = color->image_depth.buffer;
  std::vector<glm::vec4> vec_rgba;

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

      //Retrieve color
      int color_idx = i * 4;
      float r = static_cast<float>(color_data[color_idx + 2]) / 255.0f;
      float g = static_cast<float>(color_data[color_idx + 1]) / 255.0f;
      float b = static_cast<float>(color_data[color_idx])     / 255.0f;
      float a = static_cast<float>(color_data[color_idx + 3]) / 255.0f;
      vec_rgba.push_back(vec4(r, g, b, a));
    }
  }

  eng::structure::Object* object = k4a_device->get_object();
  object->xyz = vec_xyz;
  object->rgb = vec_rgba;

  //---------------------------
}
void Cloud::retrieve_color(K4A_device* k4a_device){
  //---------------------------



  //---------------------------
}

}
