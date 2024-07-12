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
  this->rad_model = node_correction->get_rad_model();
  this->rad_io_model = node_correction->get_rad_io_model();
  this->dat_image = node_data->get_dat_image();
  this->dat_selection = node_data->get_dat_selection();
  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::make_image_correction(dyn::base::Sensor* sensor, utl::media::Image* ir){
  if(sensor == nullptr || ir == nullptr) return;
  //---------------------------

  if(!rad_model->is_model_loaded(sensor)){
    rad_io_model->import_model(sensor);
    return;
  }

  std::vector<uint8_t> vec_data = ir->data;
  this->make_correction(sensor, ir, vec_data);
  this->update_correction_image(sensor, ir, vec_data);

  //---------------------------
}

//Subfunction
void Correction::make_correction(dyn::base::Sensor* sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data){
  //---------------------------

  utl::base::Data* data = &sensor->data;
  std::vector<float>& vec_R = utl_attribut->get_attribut_data(data, "R");
  std::vector<float>& vec_It = utl_attribut->get_attribut_data(data, "It");
  std::vector<float> Is_cor = std::vector<float>(data->xyz.size(), 0.0f);

  #pragma omp parallel for
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      int idx = y * ir->width + x;

      //Get parameters
      float I_cor = 0;
      float I_raw = sensor->buffer_ir[idx];

      //If to prevent correction of image borders
      if(I_raw != 0){
        float& It = vec_It[idx];
        float& R  = vec_R[idx];

        I_cor = apply_correction(I_raw, R, It);
      }

      //Set image value
      int idp = idx * 4;
      uint8_t p_cor = static_cast<uint8_t>(I_cor * 255.0f);
      vec_data[idp]     = p_cor;
      vec_data[idp + 1] = p_cor;
      vec_data[idp + 2] = p_cor;

      Is_cor[idx] = I_cor;
    }
  }

  data->Is_cor = Is_cor;

  //---------------------------
}
void Correction::update_correction_image(dyn::base::Sensor* sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data){
  //---------------------------

  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::CORRECTION);
  image->name = "Correction";
  image->width = ir->width;
  image->height = ir->height;
  image->size = ir->size;
  image->format = ir->format;
  image->data = vec_data;
  image->timestamp = ir->timestamp;

  //---------------------------
}
float Correction::apply_correction(float I_raw, float R, float It){
  if(isnan(It)) return 0;
  //---------------------------

  float fit = rad_model->apply_model(R, It);
  float I_cor = (I_raw / fit) * 0.5;
  I_cor = std::min(I_cor, 1.0f);

  //---------------------------
  return I_cor;
}

}
