#include "Object.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace utl::entity{

//Constructor / Destructor
Object::Object(){
  //---------------------------

  this->entity_type = "entity::Object";
  this->data.unicolor = math::random();

  this->node_vulkan = nullptr;
  this->node_camera = nullptr;

  //---------------------------
}
Object::Object(eng::Node* node_engine){
  //---------------------------

  this->entity_type = "entity::Object";
  this->data.unicolor = math::random();

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
void Object::clear_data(){
  //----------------------------

  this->data.xyz.clear();
  this->data.rgb.clear();
  this->data.uv.clear();
  this->data.Nxyz.clear();
  this->data.ts.clear();
  this->data.Is.clear();

  //----------------------------
  this->update_data();
}
void Object::update_data(){
  if(node_camera == nullptr) cout<<"[error] Object - no  engine initalization"<<endl;
  vk::main::Engine* vk_engine = node_vulkan->get_vk_engine();
  //----------------------------

  //Update own data
  vk_engine->insert_data(&data, &pose);

  //----------------------------
}
void Object::update_pose(){
  if(node_camera == nullptr) cout<<"[error] Object - no engine initalization"<<endl;
  cam::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  //Update own pose
  cam_control->compute_camera_mvp(&pose);

  //Update own glyph pose
  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->update_pose(this);
  }

  //----------------------------
}
void Object::update_glyph(){
  //----------------------------

  //Update own glyph data
  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->update_glyph(this);
    glyph->update_data();
  }

  //----------------------------
}
void Object::remove_entity(){
  vk::main::Engine* vk_engine = node_vulkan->get_vk_engine();
  //----------------------------

  //Remove glyph data
  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->clear();
  }

  //Remove this data
  vk_engine->remove_data(&data);

  //----------------------------
}
void Object::reset_entity(){
  //---------------------------

  pose.min = glm::vec3(0.0f);
  pose.max = glm::vec3(0.0f);
  pose.root = glm::vec3(0.0f);
  pose.COM = glm::vec3(0.0f);

  pose.rotat = glm::mat4(1.0f);
  pose.trans = glm::mat4(1.0f);
  pose.scale = glm::mat4(1.0f);
  pose.model = pose.model_init;
  pose.mvp = glm::mat4(1.0f);

  //---------------------------
}

//Subfunction
void Object::set_visibility(bool value){
  if(data.is_visible == value) return;
  //---------------------------

  this->is_visible = value;
  data.is_visible = value;

  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->set_visibility(value);
  }

  //---------------------------
}
utl::entity::Glyph* Object::get_glyph(int type){
  utl::entity::Glyph* glyph = nullptr;
  //---------------------------

  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph_vec = *next(list_glyph.begin(), i);
    if(glyph_vec->get_type() == type){
      glyph = glyph_vec;
      break;
    }
  }

  //---------------------------
  return glyph;
}

}
