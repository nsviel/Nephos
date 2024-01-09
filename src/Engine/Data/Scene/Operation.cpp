#include "Operation.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4A/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Operation::Operation(eng::scene::Node* sce_node){
  //---------------------------

  Engine* engine = sce_node->get_engine();

  this->sce_database = sce_node->get_scene_database();
  this->sce_glyph = sce_node->get_scene_glyph();
  this->eng_camera = engine->get_eng_camera();
  this->ope_transform = new eng::ope::Transformation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::update_entity(eng::data::Entity* entity){
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    eng_camera->compute_cam_mvp(object);
    sce_glyph->update_glyph_object(object);
  }
  //K4A device entity
  else if(K4A_device* device = dynamic_cast<K4A_device*>(entity)){
    eng_camera->compute_cam_mvp(device->cloud.object);
    sce_glyph->update_glyph_object(device->cloud.object);
  }

  //---------------------------
}
void Operation::remove_entity(eng::data::Entity* entity){
  //---------------------------



  //---------------------------
}
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
