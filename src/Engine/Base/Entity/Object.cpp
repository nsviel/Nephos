#include "Object.h"

#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Utility/Function/Math/fct_math.h>


namespace eng::data{

//Constructor / Destructor
Object::Object(){
  //---------------------------

  this->unicolor = math::random_color();
  this->type = "Object";

  //---------------------------
}
Object::Object(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->unicolor = math::random_color();
  this->type = "Object";

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::update_entity(){
  eng::camera::Node* node_camera = engine->get_node_camera();
  eng::camera::Control* cam_control = node_camera->get_camera_control();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  cam_control->compute_camera_mvp(this);
  sce_glyph->update_glyph_object(this);

  //----------------------------
}
void Object::remove_entity(){
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  VK_engine* vk_engine = eng_vulkan->get_vk_engine();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  sce_glyph->remove_glyph_object(this);
  vk_engine->remove_object_in_engine(this);

  //----------------------------
}
void Object::reset_entity(){
  //---------------------------

  this->min = glm::vec3(0.0f);
  this->max = glm::vec3(0.0f);
  this->root = glm::vec3(0.0f);
  this->COM = glm::vec3(0.0f);

  this->rotat = glm::mat4(1.0f);
  this->trans = glm::mat4(1.0f);
  this->scale = glm::mat4(1.0f);
  this->model = glm::mat4(1.0f);
  this->mvp = glm::mat4(1.0f);

  //---------------------------
}

}
