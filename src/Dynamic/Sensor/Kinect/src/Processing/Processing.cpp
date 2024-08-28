#include "Processing.h"

#include <Kinect/Namespace.h>
#include <Core/Namespace.h>
#include <Profiler/Namespace.h>
#include <Processing/Namespace.h>


namespace k4n{

//Constructor / Destructor
Processing::Processing(k4n::Node* node_k4n){
  //---------------------------

  core::Node* node_core = node_k4n->get_node_core();
  dyn::prc::Node* node_processing = node_k4n->get_node_processing();

  this->thread_pool = node_core->get_thread_pool();
  this->k4n_image = new k4n::processing::image::Data(node_k4n);
  this->k4n_cloud = new k4n::processing::cloud::Data(node_k4n);
  this->dyn_ope_image = node_processing->get_ope_image();
  this->dyn_ope_cloud = node_processing->get_ope_cloud();

  //---------------------------
}
Processing::~Processing(){}

//Main function
void Processing::start_thread(k4n::base::Sensor& sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, &sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Processing::run_thread(k4n::base::Sensor& sensor){
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
  dyn_ope_cloud->wait_operation();

  //---------------------------
}

//Subfunction
void Processing::image_processing(k4n::base::Sensor& sensor){
  //---------------------------

  k4n_image->extract_data(sensor);
  //dyn_ope_image->start_thread(sensor);

  //---------------------------
}
void Processing::cloud_processing(k4n::base::Sensor& sensor){
  //---------------------------

  k4n_cloud->extract_data(sensor);
  dyn_ope_cloud->run_operation(sensor);

  //---------------------------
}

}
