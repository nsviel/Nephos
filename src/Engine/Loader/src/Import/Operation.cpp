#include "Operation.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::importer{

//Constructor / Destructor
Operation::Operation(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->ldr_transformation = node_loader->get_ldr_transformation();
  this->dat_entity = node_data->get_dat_entity();
  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_dat_set();
  this->dat_glyph = node_data->get_dat_glyph();
  this->dat_selection = node_data->get_dat_selection();
  this->ope_transform = new ope::Transformation();
  this->ope_operation = new ope::Operation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::insert_object(dat::base::Object* object){
  if(object == nullptr) return;
  //---------------------------

  this->ope_clean();
  this->ope_color(object);
  this->ope_transformation(object);
  this->ope_insertion(object);

  //---------------------------
}
void Operation::insert_set(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  dat::base::Set* set_graph = dat_graph->get_set_graph();
  dat_set->add_subset(set_graph, set);
  set->is_locked = true;

  //---------------------------
}

//Subfunction
void Operation::ope_clean(){
  //---------------------------

  //Remove old one
  if(ldr_struct->importer.remove_old){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->remove_all_entity(set_graph);
  }

  //---------------------------
}
void Operation::ope_color(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //If no color, fill it with white
  if(entity->data.rgb.size() == 0){
    for(int i=0; i<entity->data.xyz.size(); i++){
      entity->data.rgba.push_back(glm::vec4(1, 1, 1, 1));
    }
  }else{
    for(int i=0; i<entity->data.rgb.size(); i++){
      glm::vec3& rgb = entity->data.rgb[i];
      entity->data.rgba.push_back(glm::vec4(rgb.x, rgb.y, rgb.z, 1));
    }
  }

  //---------------------------
}
void Operation::ope_transformation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Transformation
  ldr_transformation->load_transformation(entity);

  //Scaling
  ope_transform->make_scaling(&entity->pose, ldr_struct->importer.scaling);

  //Centering
  if(ldr_struct->importer.center){
    ope_operation->center_object(entity);
  }

  //---------------------------
}
void Operation::ope_insertion(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Init object into engine
  if(entity->set_parent == nullptr) entity->set_parent = dat_graph->get_set_graph();
  dat_set->insert_entity(entity->set_parent, entity);
  dat_entity->init_entity(entity);
  dat_glyph->insert_glyph(entity);
  dat_selection->select_element(entity);

  //---------------------------
}

}
