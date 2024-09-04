#include "Normal.h"

#include <Processing/Namespace.h>
#include <Core/Namespace.h>
#include <Data/Namespace.h>
#include <Profiler/Namespace.h>
#include <Thread/Namespace.h>
#include <Utility/Namespace.h>
#include <cstdlib>
#include <chrono>


namespace dyn::prc::cloud{

// Constructor / Destructor
Normal::Normal(dyn::prc::Node* node_processing){
  //---------------------------

  core::Node* node_core = node_processing->get_node_core();
  dat::Node* node_data = node_processing->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->thread_pool = node_core->get_thread_pool();
  this->dyn_struct = node_processing->get_dyn_struct();
  this->dat_image = node_element->get_dat_image();
  this->dat_glyph = node_element->get_dat_glyph();
  this->img_converter = new dat::img::Converter();
  this->atr_normal = new dat::atr::normal::Structured();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::start_thread(std::shared_ptr<dat::base::Sensor> sensor){
  if(!dyn_struct->operation.normal.enable) return;
  //---------------------------

  this->wait_thread();
  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Normal::run_thread(std::shared_ptr<dat::base::Sensor> sensor){
  prf::monitor::Tasker* tasker = sensor->profiler.fetch_tasker("dat::atr::normal");
  //---------------------------

  tasker->loop();

  //Normal
  tasker->task_begin("normal");
  this->compute_normal(sensor);
  tasker->task_end("normal");

  //Image
  tasker->task_begin("image");
  this->compute_image(sensor);
  tasker->task_end("image");

  //---------------------------
  this->thread_idle = true;
}
void Normal::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Normal::compute_normal(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  atr_normal->set_knn(dyn_struct->operation.normal.knn);
  atr_normal->compute_normal(*sensor->data);
  dyn_struct->operation.normal.time = atr_normal->get_time();
  atr_location->compute_incidence_angle(*sensor);

  //---------------------------
}
void Normal::compute_image(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  std::shared_ptr<utl::media::Image> image = dat_image->get_or_create_image(*sensor, "Normal");
  image->timestamp = sensor->timestamp.current;
  img_converter->convert_normal_to_image(*sensor->data, image);

  //dat_glyph->update_glyph(sensor, dat::base::object::NORMAL);

  //---------------------------
}

}
