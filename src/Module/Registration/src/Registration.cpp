#include "Registration.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>

namespace rad::processing{

//Constructor / Destructor
Registration::Registration(k4n::Node* node_k4n){
  //---------------------------

  rad::Node* node_radio = node_k4n->get_node_radio();

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_pool = node_k4n->get_k4n_pool();

  //---------------------------
}
Registration::~Registration(){}

//Main function
void Registration::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  k4n_pool->add_task(task_function);

  //---------------------------
}
void Registration::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("registration");
  //---------------------------

  tasker->loop_begin();


  tasker->loop_end();

  //---------------------------
  this->idle = true;
}
void Registration::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction


}
