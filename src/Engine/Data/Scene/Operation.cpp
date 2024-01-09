#include "Operation.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4A/Namespace.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>


namespace eng::scene{

//Constructor / Destructor
Operation::Operation(eng::scene::Node* sce_node){
  //---------------------------

  this->engine = sce_node->get_engine();
  this->sce_database = sce_node->get_scene_database();
  this->sce_glyph = sce_node->get_scene_glyph();
  this->eng_camera = engine->get_eng_camera();
  this->ope_transform = new eng::ope::Transformation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::update_entity(eng::data::Entity* entity){
  if(entity == nullptr) return;
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
  if(entity == nullptr) return;
  //---------------------------

  //If entity is an object
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    Vulkan* eng_vulkan = engine->get_eng_vulkan();
    VK_engine* vk_engine = eng_vulkan->get_vk_engine();

    sce_glyph->remove_glyph_object(object);
    vk_engine->remove_object_in_engine(object);
  }
  //If entity is a k4a device
  if(K4A_device* device = dynamic_cast<K4A_device*>(entity)){
    eng::capture::Node* cap_node = engine->get_eng_capture();
    eng::kinect::Kinect* kinect = cap_node->get_kinect();
    K4A_swarm* k4a_swarm = kinect->get_k4a_swarm();

    k4a_swarm->delete_device(device);
  }

  //---------------------------
}
void Operation::make_translation(eng::data::Entity* entity, vec3 translation){
  if(entity == nullptr) return;
  //---------------------------

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
void Operation::make_rotation(eng::data::Entity* entity, vec3 rotation){
  if(entity == nullptr) return;
  //---------------------------

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
