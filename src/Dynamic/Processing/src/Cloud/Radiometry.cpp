#include "Radiometry.h"

#include <Processing/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Radiometry/Correction/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::prc::cloud{

//Constructor / Destructor
Radiometry::Radiometry(dyn::prc::Node* node_processing){
  //---------------------------

  rad::Node* node_radio = node_processing->get_node_radio();
  rad::cor::Node* node_correction = node_radio->get_node_correction();

  this->rad_correction = node_correction->get_rad_correction();

  //---------------------------
}
Radiometry::~Radiometry(){}

//Main function
void Radiometry::start_thread(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Radiometry::run_thread, this, sensor);

  //---------------------------
}
void Radiometry::run_thread(std::shared_ptr<dat::base::Sensor> sensor){
  prf::monitor::Tasker* tasker = sensor->profiler.fetch_tasker("ope::correction");
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
void Radiometry::compute_correction(std::shared_ptr<dat::base::Sensor> sensor){
  utl::base::Data& data = *sensor->data;
  //---------------------------

  //Search for image
  auto it = data.map_image.find("Intensity");
  if(it == data.map_image.end()) return;

  //Apply correction on it
  rad_correction->make_image_correction(*sensor, it->second);

  //---------------------------
}

}
