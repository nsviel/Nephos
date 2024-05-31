#include "Entity.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Vulkan/Namespace.h>


namespace dat{

//Constructor / Destructor
Entity::Entity(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->node_engine = node_engine;
  this->dat_glyph = node_data->get_data_glyph();
  this->dat_struct = node_data->get_data_struct();
  this->vk_engine = node_vulkan->get_vk_engine();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(dat::base::Entity* entity){
  utl::base::Data* data = entity->get_data();
  utl::base::Pose* pose = entity->get_pose();
  //---------------------------

  //If object; create dedicated glyphs
  if(dat::base::Object* object = dynamic_cast<dat::base::Object*>(entity)){
    dat_glyph->create_glyph_object(object);
  }

  //Init entity
  entity->UID = dat_struct->UID++;
  data->UID = dat_struct->UID++;
  vk_engine->insert_data(data, pose);

  //---------------------------
}
void Entity::clear_entity(dat::base::Entity* entity){
  utl::base::Data* data = entity->get_data();
  //----------------------------

  vk_engine->remove_data(data);

  //----------------------------
}
void Entity::update_data(dat::base::Entity* entity){
  utl::base::Data* data = entity->get_data();
  utl::base::Pose* pose = entity->get_pose();
  //----------------------------

  vk_engine->insert_data(data, pose);

  //----------------------------
}
void Entity::update_glyph(dat::base::Object* object){
  //----------------------------

  //Update own glyph data
  for(int i=0; i<object->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(object->list_glyph.begin(), i);
    //glyph->update_glyph(glyph);
    this->update_data(glyph);
  }

  //----------------------------
}

}
