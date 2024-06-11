#include "Correction.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  rad::correction::Node* node_correction = node_radio->get_node_correction();
  rad::model::Node* node_model = node_radio->get_node_model();

  this->rad_struct = node_correction->get_rad_struct();
  this->model_sphere = node_model->get_model_sphere();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::make_image_correction(dyn::base::Sensor* sensor, utl::media::Image* ir, utl::media::Image* depth){
  if(model_sphere->is_ready() == false) return;
  //---------------------------

  utl::base::Data* data = &sensor->data;

  rad_struct->image.data = ir->data;
  rad_struct->image.width = ir->width;
  rad_struct->image.height = ir->height;
  rad_struct->image.size = ir->size;
  rad_struct->image.format = ir->format;
tic();

  #pragma omp parallel for
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      int idx = y * ir->width + x;

      //Get parameters
      float I_cor = 0;
      float I_raw = sensor->buffer_ir[idx];
      if(I_raw != 0){
        vec3 Nxyz = data->Nxyz[idx];
        vec3 xyz = sensor->convert_depth_2d_to_3d(ivec2(x, y));
        float It = math::compute_It(xyz, Nxyz, glm::vec3(0, 0, 0));
        float R = math::distance_from_origin(xyz);

        //I_cor = apply_correction(I_raw, R, It);
        I_cor *= 255.0f;
      }

      //Set image value
      int idp = idx * 4;
      uint8_t p_cor = static_cast<uint8_t>(I_cor);
      rad_struct->image.data[idp]     = static_cast<uint8_t>(p_cor);
      rad_struct->image.data[idp + 1] = static_cast<uint8_t>(p_cor);
      rad_struct->image.data[idp + 2] = static_cast<uint8_t>(p_cor);
    }
  }
toc_us("hey");

  rad_struct->image.new_data = true;

  //---------------------------
}

//Subfunction
float Correction::apply_correction(float I_raw, float R, float It){
  if(isnan(It)) return 0;
  //---------------------------

  float fit = model_sphere->apply_model(R, It);
  float I_cor = (I_raw / fit) * 0.25;
  I_cor = std::min(I_cor, 1.0f);

  //---------------------------
  return I_cor;
}

}
