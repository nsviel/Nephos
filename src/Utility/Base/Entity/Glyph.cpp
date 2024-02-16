#include "Glyph.h"

#include <Engine/Node.h>
#include <Engine/Camera/Namespace.h>
#include <Vulkan/Node.h>
#include <Vulkan/VK_main/Graphical.h>
#include <Utility/Function/Math/Math.h>


namespace utl::entity{

//Constructor / Destructor
Glyph::Glyph(eng::Node* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->pose = new utl::type::Pose();
  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->type = "Glyph";

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::update_data(){
  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  for(int i=0; i<vec_data.size(); i++){
    vk_graphical->insert_data_in_engine(vec_data[i], pose);
  }

  //----------------------------
}
void Glyph::update_pose(){
  eng::cam::Node* node_camera = node_engine->get_node_camera();
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  for(int i=0; i<vec_data.size(); i++){
    cam_control->compute_camera_mvp(pose);
  }

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
