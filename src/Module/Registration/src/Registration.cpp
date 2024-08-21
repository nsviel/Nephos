#include "Registration.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>

namespace rad::processing{

//Constructor / Destructor
Registration::Registration(k4n::Node* node_k4n){
  //---------------------------

  core::Node* node_core = node_k4n->get_node_core();

  this->thread_pool = node_core->get_thread_pool();

  //---------------------------
}
Registration::~Registration(){}

//Main function
void Registration::start_thread(k4n::base::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Registration::run_thread(k4n::base::Sensor* sensor){
  //prf::monitor::Tasker* tasker = sensor->profiler->fetch_tasker("registration");
  //---------------------------

  //tasker->loop_begin();


  //tasker->loop_end();

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
