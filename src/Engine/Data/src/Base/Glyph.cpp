#include "Glyph.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::base{

//Constructor / Destructor
Glyph::Glyph(eng::Node* node_engine){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->entity_type = "entity::Glyph";

  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();
  this->node_data = node_engine->get_node_data();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::init(){
  dat::Entity* dat_entity = node_data->get_entity();
  //----------------------------

  dat_entity->init_entity(this);

  //----------------------------
}
void Glyph::clear(){
  vk::main::Engine* vk_engine = node_vulkan->get_vk_engine();
  //----------------------------

  vk_engine->remove_data(&data);

  //----------------------------
}

//Subfunction
void Glyph::update_data(){
  vk::main::Engine* vk_engine = node_vulkan->get_vk_engine();
  //----------------------------

  vk_engine->insert_data(&data, &pose);

  //----------------------------
}
void Glyph::update_pose(){
  cam::Control* cam_control = node_camera->get_control();
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
