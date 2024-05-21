#include "Correction.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>


namespace rad{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_model = node_radio->get_rad_model();
  this->ope_normal = new ope::attribut::Normal();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::apply_correction(dat::base::Sensor* sensor, utl::media::Image* ir, utl::media::Image* depth){
  //---------------------------


  if(rad_model->is_ready() == false) return;

  rad_struct->correction.image.data = ir->data;
  rad_struct->correction.image.width = ir->width;
  rad_struct->correction.image.height = ir->height;
  rad_struct->correction.image.size = ir->size;
  rad_struct->correction.image.format = ir->format;

  vector<glm::vec3> vec_Nxyz;
  this->compute_normal(depth, vec_Nxyz);

/*
  vec3 root = vec3(0, 0, 0);
  int cpt = 0;
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      // Compute the index of the current pixel
      int idx = (y * ir->width + x) * 2;


      uint16_t value = ir->data[idx] | (ir->data[idx + 1] << 8);
      float I_raw = static_cast<float>(value);
      vec3 Nxyz = vec_Nxyz[cpt++];
      vec3 xyz  = sensor->convert_depth_2d_to_3d(ivec2(x, y));
      float It = ope_normal->compute_It(xyz, Nxyz, root);
      float R = math::distance_from_origin(xyz);

      float I_cor;
      if(isnan(It)){
        I_cor = 0;
      }else{
        float fit = rad_model->apply_model(R, It);
        I_cor = I_raw / fit;


        if(I_cor > 1) I_cor = 255;
        else I_cor = 0;
      }

 I_cor = 255;

      uint16_t I_cor_value = static_cast<uint16_t>(I_cor);
      rad_struct->correction.image.data[idx] = I_cor_value & 0xFF;
      rad_struct->correction.image.data[idx + 1] = (I_cor_value >> 8) & 0xFF;

    }
  }
  */

  //Try to turn all the ir in white to be sure all conversion is ok
  vec3 root = vec3(0, 0, 0);
  int cpt = 0;
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      // Compute the index of the current pixel
      int idx = (y * ir->width + x) * 2;


      uint16_t value = ir->data[idx] | (ir->data[idx + 1] << 8);
      float I_raw = static_cast<float>(value);

      I_raw = 60000;


      uint16_t I_cor_value = static_cast<uint16_t>(I_raw);
      rad_struct->correction.image.data[idx] = I_cor_value & 0xFF;
      rad_struct->correction.image.data[idx + 1] = (I_cor_value >> 8) & 0xFF;

    }
  }

  rad_struct->correction.image.new_data = true;


  //---------------------------
}

//Subfunction
void Correction::compute_normal(utl::media::Image* depth, vector<glm::vec3>& vec_Nxyz){
  //---------------------------

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
