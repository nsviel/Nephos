#include "Finalizer.h"

#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Profiler/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Finalizer::Finalizer(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_dynamic->get_node_engine();
  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_entity = node_data->get_dat_entity();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->ope_colorizer = new ope::color::Colorizer();
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Finalizer::~Finalizer(){}

//Main function
void Finalizer::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  this->wait_thread();
  auto task_function = [this, sensor](){
    this->thread_function(sensor);
  };
  this->thread_idle = false;
  thread_pool->add_task(task_function);

  //---------------------------
}
void Finalizer::thread_function(dyn::base::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("ope::finalizer");
  //---------------------------

  tasker->loop();

  //Colorization
  tasker->task_begin("colorization");
  this->colorize_object(sensor);
  tasker->task_end("colorization");

  //Update
  tasker->task_begin("update");
  this->update_object(sensor);
  tasker->task_end("update");

  //---------------------------
  this->thread_idle = true;
}
void Finalizer::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  //---------------------------
}

//Subfunction
void Finalizer::colorize_object(dyn::base::Sensor* sensor){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = dyn_struct->colorization.color_mode;
  config.heatmap_mode = dyn_struct->colorization.heatmap_mode;
  config.intensity_diviser = dyn_struct->operation.intensity.diviser;
  config.heatmap_range_height = dyn_struct->colorization.range_height;
  config.unicolor = dyn_struct->colorization.unicolor;

  ope_colorizer->make_colorization(sensor, config);

  //---------------------------
}
void Finalizer::update_object(dyn::base::Sensor* sensor){
  //---------------------------

  dat_entity->update_data(sensor);
  //dat_entity->update_glyph(sensor->get_object());

  //---------------------------
}

}
