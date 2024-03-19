#include "Glyph.h"

#include <Engine/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Function/Math/Math.h>


namespace utl::entity{

//Constructor / Destructor
Glyph::Glyph(eng::Node* node_engine){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->entity_type = "entity::Glyph";

  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::clear(){
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  vk_graphical->remove_data_in_engine(&data);

  //----------------------------
}
void Glyph::update_data(){
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  vk_graphical->insert_data_in_engine(&data, &pose);

  //----------------------------
}
void Glyph::update_pose(){
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  cam_control->compute_camera_mvp(&pose);

  //----------------------------
}
void Glyph::update_pose(utl::type::Entity* entity){
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  cam_control->compute_camera_mvp(&pose);

  //----------------------------
}
void Glyph::set_visibility(bool value){
  //---------------------------

  this->is_visible = value;
  data.is_visible = value;

  //---------------------------
}


}
