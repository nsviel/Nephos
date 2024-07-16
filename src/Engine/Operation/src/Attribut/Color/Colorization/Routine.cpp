#include "Routine.h"

#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Profiler/Namespace.h>


namespace ope::color{

//Constructor / Destructor
Routine::Routine(ope::Node* node_operation){
  //---------------------------

  this->ope_struct = node_operation->get_ope_struct();
  this->ope_colorizer = new ope::color::Colorizer();

  //---------------------------
}
Routine::~Routine(){}

//Main function
void Routine::colorize_element(utl::base::Element* element){
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    this->colorize_set(set);
  }else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->colorize_entity(entity);
  }

  //---------------------------
}

//Subfunction
void Routine::colorize_set(dat::base::Set* set){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    this->colorize_entity(entity);
  }

  //---------------------------
}
void Routine::colorize_entity(dat::base::Entity* entity){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = ope_struct->attribut.color.mode;
  config.heatmap_mode = ope_struct->attribut.heatmap.mode;
  config.intensity_diviser = ope_struct->attribut.intensity.diviser;
  config.heatmap_range_height = ope_struct->attribut.color.range;
  config.unicolor = ope_struct->attribut.color.unicolor;

  ope_colorizer->make_colorization(entity, config);

  //---------------------------
}

}
