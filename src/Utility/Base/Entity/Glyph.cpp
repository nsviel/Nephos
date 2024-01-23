#include "Glyph.h"

#include <Engine/Engine.h>
#include <Engine/Camera/Namespace.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Utility/Function/Math/fct_math.h>


namespace utl::entity{

//Constructor / Destructor
Glyph::Glyph(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->pose = new utl::type::Pose();
  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->type = "Glyph";

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::update_entity(){
  camera::src::Node* node_camera = engine->get_node_camera();
  camera::src::Control* cam_control = node_camera->get_camera_control();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  VK_engine* vk_engine = eng_vulkan->get_vk_engine();
  //----------------------------

  for(int i=0; i<vec_data.size(); i++){
    vk_engine->insert_data_in_engine(vec_data[i], pose);
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
