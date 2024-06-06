#include "Operation.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Operation::Operation(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->ldr_struct = node_loader->get_ldr_struct();
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

//Main functions
void Operation::insert_object(dat::base::Object* object){
  if(object == nullptr) return;
  //---------------------------

  //Operation
  this->ope_misc(object);
  this->ope_color(object);
  this->ope_transformation(object);

  //Init object into engine
  if(object->set_parent == nullptr) object->set_parent = dat_graph->get_set_graph();
  dat_set->insert_entity(object->set_parent, object);
  dat_entity->init_entity(object);
  dat_glyph->insert_glyph(object);
  dat_selection->select_element(object);

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
void Operation::ope_misc(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Remove old one
  if(ldr_struct->import_remove_old){
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
      entity->data.rgba.push_back(vec4(1, 1, 1, 1));
    }
  }else{
    for(int i=0; i<entity->data.rgb.size(); i++){
      glm::vec3& rgb = entity->data.rgb[i];
      entity->data.rgba.push_back(vec4(rgb.x, rgb.y, rgb.z, 1));
    }
  }

  //---------------------------
}
void Operation::ope_transformation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Transformation
  std::string& path = entity->data.path.transformation;


  glm::mat4 mat = utl::transformation::find_transformation_from_file(path);
  entity->pose.model = mat;
  entity->pose.model_init = mat;

  //Scaling
  ope_transform->make_scaling(entity, ldr_struct->import_scaling);

  //Centering
  if(ldr_struct->import_center){
    ope_operation->center_object(entity);
  }

  //---------------------------
}

}
