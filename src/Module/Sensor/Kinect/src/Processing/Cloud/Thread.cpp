#include "Thread.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::processing::cloud{

//Constructor / Destructor
Thread::Thread(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dyn::Node* node_dynamic = node_engine->get_node_dynamic();

  this->thread_pool = node_engine->get_thread_pool();
  this->dyn_operation = node_dynamic->get_ope_cloud();
  this->k4n_data = new k4n::processing::cloud::Data(node_k4n);

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  this->thread_idle = false;
  thread_pool->add_task(task_function);

  //---------------------------
}
void Thread::run_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->extract_data(sensor);
  this->run_operation(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Thread::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  dyn_operation->wait_operation();

  //---------------------------
}

//Subfunction
void Thread::extract_data(k4n::structure::Sensor* sensor){
  //---------------------------

  k4n_data->convert_image_into_cloud(sensor);

  //---------------------------
}
void Thread::run_operation(k4n::structure::Sensor* sensor){
  //---------------------------

  //Dynamic operation
  dyn_operation->run_operation(sensor);

  //---------------------------
}

}
