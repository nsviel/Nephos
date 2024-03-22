#include "Matching.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Matching::Matching(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_pool = node_k4n->get_k4n_pool();
  this->k4n_detector = new k4n::detection::Detector(node_k4n);

  //---------------------------
}
Matching::~Matching(){}

//Main function
void Matching::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  k4n_pool->add_task(task_function);

  //---------------------------
}
void Matching::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("calibration");
  //---------------------------

  tasker->loop_begin();

  tasker->task_begin("detection");
  k4n_detector->make_sphere_detection(sensor);
  tasker->task_end("detection");

  tasker->task_begin("detection");
  k4n_detector->make_sphere_detection(sensor);
  tasker->task_end("detection");

  tasker->loop_end();

  //---------------------------
  this->idle = true;
}
void Matching::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction


}
