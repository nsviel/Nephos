#include "Operation.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4A/Namespace.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>


namespace eng::scene{

//Constructor / Destructor
Operation::Operation(eng::scene::Node* node_scene){
  //---------------------------

  this->engine = node_scene->get_engine();
  this->sce_database = node_scene->get_scene_database();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->node_camera = engine->get_node_camera();
  this->ope_transform = new eng::ope::Transformation();
  this->ope_operation = new eng::ope::Operation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::update_entity(eng::data::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    node_camera->compute_cam_mvp(object);
    sce_glyph->update_glyph_object(object);
  }
  //Glyph entity
  else if(eng::data::Glyph* glyph = dynamic_cast<eng::data::Glyph*>(entity)){
    vector<eng::data::Object*> vec_object = glyph->get_vec_object();
    for(int i=0; i<vec_object.size(); i++){
      node_camera->compute_cam_mvp(vec_object[i]);
    }
  }
  //K4A device entity
  else if(K4A_device* device = dynamic_cast<K4A_device*>(entity)){
    node_camera->compute_cam_mvp(device->cloud.object);
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
    eng::capture::Node* node_capture = engine->get_node_capture();
    eng::kinect::Node* node_kinect = node_capture->get_node_kinect();
    K4A_swarm* k4a_swarm = node_kinect->get_k4a_swarm();

    k4a_swarm->close_device(device);
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
void Operation::make_center(eng::data::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Object entity
  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_operation->center_object(object);
  }
  //K4A device entity
  else if(K4A_device* device = dynamic_cast<K4A_device*>(entity)){
    ope_operation->center_object(device->cloud.object);
  }

  //---------------------------
}


}
