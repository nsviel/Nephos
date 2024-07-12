#include "Normal.h"

#include <Dynamic/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <cstdlib>
#include <chrono>


namespace dyn::cloud{

// Constructor / Destructor
Normal::Normal(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_dynamic->get_node_engine();
  dat::Node* node_data = node_dynamic->get_node_data();

  this->thread_pool = node_engine->get_thread_pool();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dat_image = node_data->get_dat_image();
  this->dat_glyph = node_data->get_dat_glyph();
  this->ope_converter = new ope::image::Converter();
  this->ope_normal = new ope::normal::Structured();
  this->ope_attribut = new ope::attribut::Attribut();

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::start_thread(dyn::base::Sensor* sensor){
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
void Normal::run_thread(dyn::base::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("ope::normal");
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
void Normal::compute_normal(dyn::base::Sensor* sensor){
  //---------------------------

  ope_normal->set_knn(dyn_struct->operation.normal.knn);
  ope_normal->compute_normal(&sensor->data);
  dyn_struct->operation.normal.time = ope_normal->get_time();
  ope_attribut->compute_incidence_angle(sensor);

  //---------------------------
}
void Normal::compute_image(dyn::base::Sensor* sensor){
  //---------------------------

  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::NORMAL);
  image->timestamp = sensor->timestamp.current;
  ope_converter->convert_normal_to_image(&sensor->data, image);

  //dat_glyph->update_glyph(sensor, dat::base::object::NORMAL);

  //---------------------------
}

}
