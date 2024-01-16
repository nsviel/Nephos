#include "Object.h"

#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Utility/Function/Math/fct_math.h>


namespace entity{

//Constructor / Destructor
Object::Object(){
  //---------------------------

  this->type = "Object";
  this->data = new utl::base::Data();
  this->data->unicolor = math::random_color();

  //---------------------------
}
Object::Object(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->type = "Object";
  this->data = new utl::base::Data();
  this->data->unicolor = math::random_color();

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

  cam_control->compute_camera_mvp(data);
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
void Object::visibility_entity(bool value){
  //---------------------------

  this->set_visibility(value);

  for(int i=0; i<list_glyph.size(); i++){
    entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->visibility_entity(value);
  }

  //---------------------------
}
void Object::reset_entity(){
  //---------------------------

  data->min = glm::vec3(0.0f);
  data->max = glm::vec3(0.0f);
  data->root = glm::vec3(0.0f);
  data->COM = glm::vec3(0.0f);

  data->rotat = glm::mat4(1.0f);
  data->trans = glm::mat4(1.0f);
  data->scale = glm::mat4(1.0f);
  data->model = glm::mat4(1.0f);
  data->mvp = glm::mat4(1.0f);

  //---------------------------
}

}
