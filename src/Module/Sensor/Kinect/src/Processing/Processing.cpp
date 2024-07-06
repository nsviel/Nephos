#include "Processing.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n{

//Constructor / Destructor
Processing::Processing(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->thread_pool = node_engine->get_thread_pool();
  this->k4n_image = new k4n::processing::image::Thread(node_k4n);
  this->k4n_cloud = new k4n::processing::cloud::Thread(node_k4n);

  //---------------------------
}
Processing::~Processing(){}

//Main function
void Processing::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Processing::run_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->image_processing(sensor);
  this->cloud_processing(sensor);





  //---------------------------
  this->thread_idle = true;
}
void Processing::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_image->wait_thread();
  k4n_cloud->wait_thread();

  //---------------------------
}

//Subfunction
void Processing::image_processing(k4n::structure::Sensor* sensor){
  //---------------------------

  k4n_image->extract_data(sensor);
  k4n_image->run_operation(sensor);

  //---------------------------
}
void Processing::cloud_processing(k4n::structure::Sensor* sensor){
  //---------------------------

  k4n_cloud->extract_data(sensor);
  k4n_cloud->run_operation(sensor);

  //---------------------------
}

}
