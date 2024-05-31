#include "Object.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Data/Namespace.h>


namespace dat::base{

//Constructor / Destructor
Object::Object(){
  //---------------------------

  this->entity_type = "entity::Object";
  this->data.unicolor = math::random();

  //---------------------------
}
Object::Object(eng::Node* node_engine){
  //---------------------------

  dat::Node* node_data = node_engine->get_node_data();

  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();
  this->dat_entity = node_data->get_dat_entity();

  this->entity_type = "entity::Object";
  this->data.unicolor = math::random();

  //---------------------------
}
Object::~Object(){}

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
}
void Object::reset(){
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
dat::base::Glyph* Object::get_glyph(int type){
  dat::base::Glyph* glyph = nullptr;
  //---------------------------

  for(int i=0; i<list_glyph.size(); i++){
    dat::base::Glyph* glyph_vec = *next(list_glyph.begin(), i);
    if(glyph_vec->get_type() == type){
      glyph = glyph_vec;
      break;
    }
  }

  //---------------------------
  return glyph;
}

}
