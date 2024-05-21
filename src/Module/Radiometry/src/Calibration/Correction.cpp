#include "Correction.h"

#include <Radiometry/Namespace.h>


namespace rad{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_model = node_radio->get_rad_model();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::apply_correction(utl::media::Image* ir, utl::media::Image* depth){
  //---------------------------




  this->compute_normal(depth);




  //---------------------------
}

//Subfunction
void Correction::compute_normal(utl::media::Image* depth){
  //---------------------------

  vector<glm::vec3> vec_Nxyz;
  vec_Nxyz.resize(depth->width * depth->height);

  for(int y = 0; y < depth->height; ++y){
    for(int x = 0; x < depth->width; ++x){
      // Compute the index of the current pixel
      int idx = y * depth->width + x;

      // Compute neighboring pixel indices
      int idx_left = std::max(x - 1, 0) + y * depth->width;
      int idx_right = std::min(x + 1, depth->width - 1) + y * depth->width;
      int idx_up = x + std::max(y - 1, 0) * depth->width;
      int idx_down = x + std::min(y + 1, depth->height - 1) * depth->width;

      // Retrieve depth values of neighboring pixels
      float depth_center = static_cast<float>(depth->data[idx]);
      float depth_left = static_cast<float>(depth->data[idx_left]);
      float depth_right = static_cast<float>(depth->data[idx_right]);
      float depth_up = static_cast<float>(depth->data[idx_up]);
      float depth_down = static_cast<float>(depth->data[idx_down]);

      // Compute central differences for x and y gradients
      float gradient_x = (depth_right - depth_left) / 2.0f;
      float gradient_y = (depth_down - depth_up) / 2.0f;

      // Compute the normal using the gradients
      glm::vec3 normal = glm::vec3(-gradient_x, -gradient_y, 1.0f);
      float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
      if (length > 0) {
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
      }

      // Store the normal
      vec_Nxyz[idx] = normal;
    }
  }

  //---------------------------
}

}
