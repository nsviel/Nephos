#include "Correction.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Correction::Correction(rad::correction::Node* node_correction){
  //---------------------------

  rad::Node* node_radio = node_correction->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_correction->get_rad_struct();
  this->model_sphere = node_correction->get_rad_model();
  this->dat_image = node_data->get_dat_image();
  this->dat_selection = node_data->get_dat_selection();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::loop(){
  if(!model_sphere->is_model_build()) return;
  //---------------------------

  //Verify that we have a sensor type
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::INTENSITY);
  this->make_image_correction(sensor, image);

  //---------------------------
}

//Subfunction
void Correction::make_image_correction(dyn::base::Sensor* sensor, utl::media::Image* ir){
  if(!model_sphere->is_model_build()) return;
  //---------------------------

  //Get image to correct
  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::CORRECTION);
  std::vector<uint8_t> vec_data = ir->data;
  image->width = ir->width;
  image->height = ir->height;
  image->size = ir->size;
  image->format = ir->format;


  utl::base::Data* data = &sensor->data;


tic();

  #pragma omp parallel for
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      int idx = y * ir->width + x;

      //Get parameters
      float I_cor = 0;
      float I_raw = sensor->buffer_ir[idx];
      vec3 Nxyz = data->Nxyz[idx];
      vec3 xyz = data->xyz[idx];

      //If to prevent correction of image borders
      if(I_raw != 0){
        float It = math::compute_It(xyz, Nxyz, glm::vec3(0, 0, 0));
        float R = math::distance_from_origin(xyz);

        I_cor = apply_correction(I_raw, R, It);
        I_cor *= 255.0f;
      }

      //Set image value
      int idp = idx * 4;
      uint8_t p_cor = static_cast<uint8_t>(I_cor);
      vec_data[idp]     = static_cast<uint8_t>(p_cor);
      vec_data[idp + 1] = static_cast<uint8_t>(p_cor);
      vec_data[idp + 2] = static_cast<uint8_t>(p_cor);

      data->Is[idx] = I_cor;
    }
  }
toc_us("hey");
image->data = vec_data;
  image->timestamp = ir->timestamp;

  //---------------------------
}
float Correction::apply_correction(float I_raw, float R, float It){
  if(isnan(It)) return 0;
  //---------------------------

  float fit = model_sphere->apply_model(R, It);
  float I_cor = (I_raw / fit) * 0.5;
  I_cor = std::min(I_cor, 1.0f);

  //---------------------------
  return I_cor;
}

}
