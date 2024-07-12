#include "Colorizer.h"

#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Profiler/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Colorizer::Colorizer(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_dynamic->get_node_engine();
  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_entity = node_data->get_dat_entity();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->ope_colorizer = new ope::color::Colorizer();
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Colorizer::~Colorizer(){}

//Main function
void Colorizer::thread_task(){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("ope::finalizer");
  //---------------------------

  tasker->loop();

  //Colorization
  tasker->task_begin("colorization");
  this->colorize_entity(sensor);
  tasker->task_end("colorization");

  //---------------------------
  this->thread_idle = true;
}

//Subfunction
void Colorizer::colorize_element(utl::base::Element* element){
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    this->colorize_set(set);
  }else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->colorize_entity(entity);
  }

  //---------------------------
}
void Colorizer::colorize_set(dat::base::Set* set){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    this->colorize_entity(entity);
  }

  //---------------------------
}
void Colorizer::colorize_entity(dat::base::Entity* entity){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = dyn_struct->colorization.color_mode;
  config.heatmap_mode = dyn_struct->colorization.heatmap_mode;
  config.intensity_diviser = dyn_struct->operation.intensity.diviser;
  config.heatmap_range_height = dyn_struct->colorization.range_height;
  config.unicolor = dyn_struct->colorization.unicolor;

  ope_colorizer->make_colorization(entity, config);
  dat_entity->update_data(entity);
  //dat_entity->update_glyph(sensor->get_object());

  //---------------------------
}

}
