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
void Detection::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Detection::run_thread, this, sensor);

  //---------------------------
}
void Detection::run_thread(dyn::base::Sensor* sensor){
  if(!model_sphere->is_model_build()) return;
  //---------------------------

  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::INTENSITY);
  this->make_image_correction(sensor, image);

  //---------------------------
  this->thread_idle = true;
}
void Detection::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

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
  std::vector<float> Is_cor = std::vector<float>(data->xyz.size(), 0.0f);


tic();
  #pragma omp parallel for
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      int idx = y * ir->width + x;

      //Get parameters
      float I_cor = 0;
      float I_raw = sensor->buffer_ir[idx];

      //If to prevent correction of image borders
      if(I_raw != 0){
        float& It = data->It[idx];
        float& R = data->R[idx];

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
toc_us("hey");
data->Is_cor = Is_cor;
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
