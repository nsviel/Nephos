#include "Object.h"

#include <Engine/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
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

  this->type = "Object";
  this->pose = new utl::type::Pose();
  this->data = new utl::type::Data();
  this->data->unicolor = math::random_color();

  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();

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
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  //Update own data
  vk_graphical->insert_data_in_engine(data, pose);

  //Update own glyph data
  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    if(glyph->is_need_update()){
      glyph->update_data();
    }
  }

  //----------------------------
}
void Object::update_pose(){
  eng::cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  //Update own pose
  cam_control->compute_camera_mvp(pose);

  //Update own glyph pose
  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->update_glyph(this);
    glyph->update_pose();
  }

  //----------------------------
}
void Object::remove_entity(){
  vk::main::Graphical* vk_graphical = node_vulkan->get_vk_graphical();
  //----------------------------

  //Remove glyph data
  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->clear();
  }

  //Remove this data
  vk_graphical->remove_data_in_engine(this->data);

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
