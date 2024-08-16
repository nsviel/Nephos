#include "Radiometry.h"

#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::prc::cloud{

//Constructor / Destructor
Radiometry::Radiometry(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();
  rad::Node* node_radio = node_dynamic->get_node_radio();
  rad::correction::Node* node_correction = node_radio->get_node_correction();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_image = node_element->get_dat_image();
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
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("ope::correction");
  //---------------------------

  tasker->loop();

  //Correction
  tasker->task_begin("correction");
  this->compute_correction(sensor);
  tasker->task_end("correction");

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

//Subfunction
void Radiometry::compute_correction(dyn::base::Sensor* sensor){
  //---------------------------

  utl::media::Image* image = dat_image->get_image(sensor, "Intensity");
  rad_correction->make_image_correction(sensor, image);

  //---------------------------
}

}
