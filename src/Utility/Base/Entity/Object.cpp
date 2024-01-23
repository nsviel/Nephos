#include "Object.h"

#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Utility/Function/Math/fct_math.h>


namespace utl::entity{

//Constructor / Destructor
Object::Object(){
  //---------------------------

  this->type = "Object";
  this->pose = new utl::type::Pose();
  this->data = new utl::type::Data();
  this->data->unicolor = math::random_color();

  //---------------------------
}
Object::Object(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->type = "Object";
  this->pose = new utl::type::Pose();
  this->data = new utl::type::Data();
  this->data->unicolor = math::random_color();

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::update_entity(){
  eng::cam::Node* node_camera = engine->get_node_camera();
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  VK_engine* vk_engine = eng_vulkan->get_vk_engine();
  //----------------------------

  cam_control->compute_camera_mvp(pose);
  vk_engine->insert_data_in_engine(data, pose);

  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->update_glyph(this);
    glyph->update_entity();
  }

  //----------------------------
}
void Object::remove_entity(){
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  VK_engine* vk_engine = eng_vulkan->get_vk_engine();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  sce_glyph->remove_glyph_object(this);
  vk_engine->remove_data_in_engine(data);

  //----------------------------
}
void Object::visibility_entity(bool value){
  //---------------------------

  this->is_visible = value;
  data->is_visible = value;

  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->visibility_entity(value);
  }

  //---------------------------
}
void Object::reset_entity(){
  //---------------------------

  pose->min = glm::vec3(0.0f);
  pose->max = glm::vec3(0.0f);
  pose->root = glm::vec3(0.0f);
  pose->COM = glm::vec3(0.0f);

  pose->rotat = glm::mat4(1.0f);
  pose->trans = glm::mat4(1.0f);
  pose->scale = glm::mat4(1.0f);
  pose->model = pose->model_init;
  pose->mvp = glm::mat4(1.0f);

  //---------------------------
}

}
