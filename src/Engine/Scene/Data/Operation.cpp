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
void Operation::make_translation(entity::Entity* entity, vec3 translation){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    ope_transform->make_translation(object->get_data(), translation);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_transform->make_translation(device->get_data(), translation);
  }

  //---------------------------
}
void Operation::make_rotation(entity::Entity* entity, vec3 rotation){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    ope_transform->make_rotation(object->get_data(), object->data->COM, rotation);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_transform->make_rotation(device->get_data(), device->cloud.object->data->COM, rotation);
  }

  //---------------------------
}
void Operation::make_rotation_X_90d(entity::Entity* entity, int value){
  //---------------------------

  //Object entity
  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    ope_attribut->compute_MinMax(object->data);
    ope_transform->make_rotation_axe_X(object->data, value * 90);
    ope_operation->elevate_object(object->data);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_attribut->compute_MinMax(device->cloud.object->data);
    ope_transform->make_rotation_axe_X(device->cloud.object->data, value * 90);
    ope_operation->elevate_object(device->cloud.object->data);
  }

  //---------------------------
}
void Operation::make_center(entity::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    ope_operation->center_object(object->data);
  }
  //K4A device entity
  else if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
    ope_operation->center_object(device->cloud.object->data);
  }

  //---------------------------
}


}
