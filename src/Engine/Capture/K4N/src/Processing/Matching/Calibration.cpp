#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  k4n::matching::Node* node_matching = node_k4n->get_node_matching();

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_pool = node_k4n->get_k4n_pool();
  this->k4n_calibration = node_matching->get_k4n_calibration();

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  k4n_pool->add_task(task_function);

  //---------------------------
}
void Calibration::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("calibration");
  //---------------------------

  tasker->loop_begin();

  tasker->task_begin("calibration");
  k4n_calibration->ransac_sphere(sensor);
  tasker->task_end("calibration");

  tasker->loop_end();

  //---------------------------
  this->idle = true;
}
void Calibration::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction


}
