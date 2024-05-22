#include "Image.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <cstdlib>


namespace ope::normal{

// Constructor / Destructor
Image::Image(){
  //---------------------------


  //---------------------------
}
Image::~Image(){}

//Main function
void Image::compute_normal_from_image(dat::base::Sensor* sensor, int width, int height, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------

  vec_Nxyz.clear();
  vec_Nxyz.resize(width * height);

  for(int y = 0; y < height; ++y){
    for(int x = 0; x < width; ++x){
      // Compute the index of the current pixel
      int idx = y * width + x;

      // Compute neighboring pixel indices
      ivec2 idx_center = ivec2(x, y);
      ivec2 idx_left = ivec2(std::max(x - 1, 0), y);
      ivec2 idx_right = ivec2(std::min(x + 1, width - 1), y);
      ivec2 idx_up = ivec2(x, std::max(y - 1, 0));
      ivec2 idx_down = ivec2(x, std::min(y + 1, height - 1));

      // Retrieve depth values of neighboring pixels
      glm::vec3 depth_center = sensor->convert_depth_2d_to_3d(idx_center);
      glm::vec3 depth_left = (x > 0) ? sensor->convert_depth_2d_to_3d(idx_left) : depth_center;
      glm::vec3 depth_right = (x < width - 1) ? sensor->convert_depth_2d_to_3d(idx_right) : depth_center;
      glm::vec3 depth_up = (y > 0) ? sensor->convert_depth_2d_to_3d(idx_up) : depth_center;
      glm::vec3 depth_down = (y < height - 1) ? sensor->convert_depth_2d_to_3d(idx_down) : depth_center;

      // Compute central differences for x and y gradients
      glm::vec3 gradient_x = (depth_right - depth_left) / 2.0f;
      glm::vec3 gradient_y = (depth_down - depth_up) / 2.0f;

      // Compute the normal using the gradients
      glm::vec3 normal = glm::cross(gradient_x, gradient_y);
      float length = glm::length(normal);
      if(length > 0){
        normal /= length;
      }

      // Compute the vector from the surface to the camera
      glm::vec3 to_camera = glm::normalize(vec3(0, 0, 0) - depth_center);
      if(glm::dot(normal, to_camera) < 0){
        // Flip the normal to point towards the camera
        normal *= -1;
      }

      // Store the normal
      vec_Nxyz[idx] = normal;
    }
  }

  //---------------------------
}

}
