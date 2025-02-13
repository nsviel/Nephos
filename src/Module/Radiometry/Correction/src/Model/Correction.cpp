#include "Correction.h"

#include <Radiometry/Correction/Namespace.h>
#include <Data/Namespace.h>


namespace rad::cor{

//Constructor / Destructor
Correction::Correction(rad::cor::Node* node_correction){
  //---------------------------

  dat::Node* node_data = node_correction->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::img::Node* node_image = node_data->get_node_image();

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();
  this->rad_io_model = node_correction->get_rad_io_model();
  this->dat_image = node_image->get_dat_image();
  this->gph_selection = node_graph->get_gph_selection();
  this->atr_field = new dat::atr::field::Manager();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::make_image_correction(dat::base::Sensor& sensor, std::shared_ptr<utl::base::Image> ir){
  if(!ir) return;
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
void Correction::make_correction(dat::base::Sensor& sensor, std::shared_ptr<utl::base::Image> ir, std::vector<uint8_t>& vec_data){
  //---------------------------

  utl::base::Data& data = *sensor.data;

  std::vector<float>& vec_R = atr_field->get_field_data(data, "R");
  std::vector<float>& vec_It = atr_field->get_field_data(data, "It");
  std::vector<float>& vec_Icor = atr_field->get_field_data(data, "I_cor");
  std::vector<float> Is_cor = std::vector<float>(data.xyz.size(), 0.0f);

  #pragma omp parallel for
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      int idx = y * ir->width + x;

      //Get parameters
      float I_cor = 0;
      float I_raw = sensor.info.buffer_ir[idx];

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

  vec_Icor = Is_cor;

  //---------------------------
}
void Correction::update_correction_image(dat::base::Sensor& sensor, std::shared_ptr<utl::base::Image> ir, std::vector<uint8_t>& vec_data){
  //---------------------------

  std::shared_ptr<utl::base::Image> image = dat_image->get_or_create_image(sensor, "Correction");
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
