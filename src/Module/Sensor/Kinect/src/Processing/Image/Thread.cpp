#include "Thread.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Thread::Thread(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dyn::Node* node_dynamic = node_engine->get_node_dynamic();

  this->k4n_cloud = new k4n::processing::Cloud(node_k4n);
  this->k4n_data = new k4n::processing::image::Data(node_k4n);
  this->thread_pool = node_engine->get_thread_pool();
  this->dyn_operation = node_dynamic->get_ope_image();

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Thread::run_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  //Retrieve data from capture
  k4n_data->find_data_from_capture(sensor);

  //Convert data into cloud
  k4n_cloud->start_thread(sensor);

  //Dynamic operation
  dyn_operation->start_thread(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Thread::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_cloud->wait_thread();
  dyn_operation->wait_thread();

  //---------------------------
}

}
