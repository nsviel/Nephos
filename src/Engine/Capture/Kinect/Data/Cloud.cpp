#include "Cloud.h"

#include <Engine/Engine.h>


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

  eng::kinect::structure::Depth* depth = &k4a_device->depth;

  // Create point cloud image
  k4a::image cloud_image = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, depth->image.width, depth->image.height, depth->image.width * 3 * (int)sizeof(int16_t));

  // Transform depth image to point cloud
  k4a_device->device.transformation.depth_image_to_point_cloud(depth->image.k4a_image, K4A_CALIBRATION_TYPE_DEPTH, cloud_image);

  // Convert point cloud data to vector<glm::vec3>
  int16_t* point_cloud_data = reinterpret_cast<int16_t*>(cloud_image.get_buffer());
  std::vector<glm::vec3> xyz;
  for(int i=0; i<cloud_image.get_size()/sizeof(int16_t); i+=3){
    int x = point_cloud_data[i];
    int y = point_cloud_data[i+1];
    int z = point_cloud_data[i+2];

    if(x != 0 && y != 0 && z != 0){
      glm::vec3 point(x/1000.0f, y/1000.0f, z/1000.0f);
      xyz.push_back(point);
    }
  }

  //---------------------------
}

}
