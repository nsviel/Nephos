#include "Operation.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>


namespace eng::scene{

//Constructor / Destructor
Operation::Operation(eng::scene::Node* node_scene){
  //---------------------------

  this->engine = node_scene->get_engine();
  this->sce_database = node_scene->get_scene_database();
  this->sce_glyph = node_scene->get_scene_glyph();
  eng::camera::Node* node_camera = engine->get_node_camera();
  this->cam_control = node_camera->get_camera_control();
  this->ope_transform = new eng::ope::Transformation();
  this->ope_operation = new eng::ope::Operation();
  this->ope_attribut = new eng::ope::Attribut();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::switch_visibility(eng::data::Set* set, bool value){
  if(set == nullptr) return;
  //---------------------------

  for(int j=0; j<set->list_entity.size(); j++){
    eng::data::Entity* entity = *next(set->list_entity.begin(), j);
    entity->entity_visibility(value);
  }

  //---------------------------
}

//Transformation
void Operation::make_translation(eng::data::Entity* entity, vec3 translation){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_transform->make_translation(object, translation);
    //cam_control->set_camera_COM(object->COM);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_transform->make_translation(device->cloud.object, translation);
    //cam_control->set_camera_COM(device->cloud.object->COM);
  }

  //---------------------------
}
void Operation::make_rotation(eng::data::Entity* entity, vec3 rotation){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_transform->make_rotation(object, object->COM, rotation);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_transform->make_rotation(device->cloud.object, device->cloud.object->COM, rotation);
  }

  //---------------------------
}
void Operation::make_rotation_X_90d(eng::data::Entity* entity, int value){
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_attribut->compute_MinMax(object);
    ope_transform->make_rotation_axe_X(object, value * 90);
    ope_operation->elevate_object(object);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_attribut->compute_MinMax(device->cloud.object);
    ope_transform->make_rotation_axe_X(device->cloud.object, value * 90);
    ope_operation->elevate_object(device->cloud.object);
  }

  //---------------------------
}
void Operation::make_center(eng::data::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_operation->center_object(object);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_operation->center_object(device->cloud.object);
  }

  //---------------------------
}


}
