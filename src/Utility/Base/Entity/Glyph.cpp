#include "Glyph.h"

#include <Engine/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Function/Math/Math.h>


namespace utl::entity{

//Constructor / Destructor
Glyph::Glyph(eng::Node* node_engine){
  //---------------------------

  this->pose = new utl::type::Pose();
  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->type = "Glyph";

  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::clear(){
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  for(int j=0; j<vec_data.size(); j++){
    vk_graphical->remove_data_in_engine(vec_data[j]);
  }

  //----------------------------
}
void Glyph::update_data(){
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  for(int i=0; i<vec_data.size(); i++){
    vk_graphical->insert_data_in_engine(vec_data[i], pose);
  }

  //----------------------------
}
void Glyph::update_pose(){
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  cam_control->compute_camera_mvp(pose);

  //----------------------------
}
void Glyph::visibility_entity(bool value){
  //---------------------------

  this->is_visible = value;
  for(int i=0; i<vec_data.size(); i++){
    utl::type::Data* data = vec_data[i];
    data->is_visible = value;
  }

  //---------------------------
}


}
