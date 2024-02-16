#include "Object.h"

#include <Engine/Node.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Vulkan/Node.h>
#include <Vulkan/VK_main/Graphical.h>
#include <Utility/Function/Math/Math.h>


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
Object::Object(eng::Node* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->type = "Object";
  this->pose = new utl::type::Pose();
  this->data = new utl::type::Data();
  this->data->unicolor = math::random_color();

  //---------------------------
}
Object::~Object(){
  //---------------------------

  //delete pose;
  //delete data

  //---------------------------
}

//Main function
void Object::update_data(){
  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  vk_graphical->insert_data_in_engine(data, pose);

  //----------------------------
}
void Object::update_pose(){
  eng::cam::Node* node_camera = node_engine->get_node_camera();
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  cam_control->compute_camera_mvp(pose);
  this->update_glyph();

  //----------------------------
}
void Object::update_glyph(){
  //----------------------------

  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->update_glyph(this);
    glyph->update_pose();
  }

  //----------------------------
}
void Object::remove_entity(){
  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  eng::scene::Node* node_scene = node_engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  sce_glyph->remove_glyph_object(this);
  vk_graphical->remove_data_in_engine(data);

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
