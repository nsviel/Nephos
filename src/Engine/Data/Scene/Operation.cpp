#include "Operation.h"

#include <Engine/Capture/K4A/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Operation::Operation(eng::scene::Node* sce_node){
  //---------------------------

  this->sce_database = sce_node->get_scene_database();
  this->ope_transform = new eng::ope::Transformation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_translation(vec3 translation){
  eng::data::Set* data_set = sce_database->get_data_set();
  //---------------------------

  eng::data::Set* set_scene = data_set->get_set("Scene");
  eng::data::Entity* entity = set_scene->selected_entity;

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_transform->make_translation(object, translation);
  }
  //K4A device entity
  else if(K4A_device* device = dynamic_cast<K4A_device*>(entity)){
    ope_transform->make_translation(device->cloud.object, translation);
  }

  //---------------------------
}
void Operation::make_rotation(vec3 rotation){
  eng::data::Set* data_set = sce_database->get_data_set();
  //---------------------------

  eng::data::Set* set_scene = data_set->get_set("Scene");
  eng::data::Entity* entity = set_scene->selected_entity;

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_transform->make_rotation(object, object->COM, rotation);
  }
  //K4A device entity
  else if(K4A_device* device = dynamic_cast<K4A_device*>(entity)){
    ope_transform->make_rotation(device->cloud.object, device->cloud.object->COM, rotation);
  }

  //---------------------------
}



}
