#include "Normal.h"

#include <Utility/Namespace.h>
#include <cstdlib>


namespace ope::image{

// Constructor / Destructor
Normal::Normal(){
  //---------------------------

  this->k = 5;

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::compute_normal(dyn::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------

  //this->compute_normal_with_gradient(sensor, width, height, vec_Nxyz);
  this->compute_normal_with_cov_img(sensor, depth, width, height, vec_Nxyz);

  //---------------------------
}

//Method function
void Normal::compute_normal_with_gradient(dyn::base::Sensor* sensor, int width, int height, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------

  vec_Nxyz.clear();
  vec_Nxyz.resize(width * height);

  for(int y = 0; y < height; ++y){
    for(int x = 0; x < width; ++x){

      // Compute the index of the current pixel
      int idx = y * width + x;

      // Compute neighboring pixel indices
      glm::ivec2 idx_center = glm::ivec2(x, y);
      glm::ivec2 idx_left = glm::ivec2(std::max(x - 1, 0), y);
      glm::ivec2 idx_right = glm::ivec2(std::min(x + 1, width - 1), y);
      glm::ivec2 idx_up = glm::ivec2(x, std::max(y - 1, 0));
      glm::ivec2 idx_down = glm::ivec2(x, std::min(y + 1, height - 1));

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
      glm::vec3 to_camera = glm::normalize(glm::vec3(0, 0, 0) - depth_center);
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
void Normal::compute_normal_with_cov(dyn::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------

  vec_Nxyz.clear();
  vec_Nxyz.resize(width * height);
tic();
  for(int y = 0; y < height; ++y){
    for(int x = 0; x < width; ++x){
      //Check
      glm::vec3 depth = sensor->convert_depth_2d_to_3d(glm::ivec2(x, y));
      if(depth == glm::vec3(0, 0, 0)) continue;

      //kNN
      std::vector<glm::vec3> vec_nn;
      this->compute_neigbor(sensor, vec_nn, x, y, width, height);

      //Normal
      glm::mat3 covariance = math::compute_covariance(vec_nn);
      glm::vec3 normal = math::compute_normal_from_covariance(covariance);

      //Orientation
      glm::vec3 to_camera = glm::normalize(glm::vec3(0, 0, 0) - depth);
      math::compute_normal_orientation(normal, to_camera);

      //Store
      int idx = y * width + x;
      vec_Nxyz[idx] = normal;
    }
  }
toc_ms("hoy");
  //---------------------------
}
void Normal::compute_normal_with_cov_img(dyn::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------

  vec_Nxyz.clear();
  vec_Nxyz.resize(width * height);

  for(int y = 1; y < height - 1; ++y){
    for(int x = 1; x < width - 1; ++x){
      // Check
      int idx = y * width + x;
      uint16_t& depth_value = sensor->buffer_depth[idx];
      if(depth_value == 0) continue;

      // Compute dzdx using both +1 and +2 pixels
      uint16_t& depth_1 = sensor->buffer_depth[idx + 1];
      uint16_t& depth_2 = sensor->buffer_depth[idx - 1];
      uint16_t& depth_3 = sensor->buffer_depth[idx + 2];
      uint16_t& depth_4 = sensor->buffer_depth[idx - 2];
      float dzdx = (depth_1 - depth_2) / 2.0f + (depth_3 - depth_4) / 4.0f;

      // Compute dzdy using both +1 and +2 pixels
      uint16_t& depth_5 = sensor->buffer_depth[(y + 1) * width + x];
      uint16_t& depth_6 = sensor->buffer_depth[(y - 1) * width + x];
      uint16_t& depth_7 = sensor->buffer_depth[(y + 2) * width + x];
      uint16_t& depth_8 = sensor->buffer_depth[(y - 2) * width + x];
      float dzdy = (depth_5 - depth_6) / 2.0f + (depth_7 - depth_8) / 4.0f;

      // Create the gradient vector and normalize it to get the normal
      glm::vec3 dz(-dzdx, -dzdy, 1.0f);
      glm::vec3 normal = glm::normalize(dz);

      // Store the normal vector in vec_Nxyz
      vec_Nxyz[idx] = normal;
    }
  }

  //---------------------------
}

//Subfunction
void Normal::compute_neigbor(dyn::base::Sensor* sensor, std::vector<glm::vec3>& vec_nn, int x, int y, int width, int height){
  //---------------------------

  int half_window = k / 2;

  // Collect neighbors
  vec_nn.clear();
  for(int ky = -half_window; ky <= half_window; ++ky){
    for(int kx = -half_window; kx <= half_window; ++kx){
      int nx = std::clamp(x + kx, 0, width - 1);
      int ny = std::clamp(y + ky, 0, height - 1);
      glm::ivec2 neighbor_idx(nx, ny);

      glm::vec3 depth = sensor->convert_depth_2d_to_3d(neighbor_idx);
      if(depth == glm::vec3(0, 0, 0)) continue;
      vec_nn.push_back(depth);
    }
  }

  //---------------------------
}

}
