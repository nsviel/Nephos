#include "Radiometry.h"

#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Radiometry::Radiometry(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();
  rad::Node* node_radio = node_dynamic->get_node_radio();
  rad::correction::Node* node_correction = node_radio->get_node_correction();

  this->dat_image = node_data->get_dat_image();
  this->rad_correction = node_correction->get_rad_correction();

  //---------------------------
}
Radiometry::~Radiometry(){}

//Main function
void Radiometry::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Radiometry::run_thread, this, sensor);

  //---------------------------
}
void Radiometry::run_thread(dyn::base::Sensor* sensor){
  //---------------------------

  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::INTENSITY);
  rad_correction->make_image_correction(sensor, image);

  //---------------------------
  this->thread_idle = true;
}
void Radiometry::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
