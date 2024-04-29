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
  this->dat_database = node_data->get_database();
  this->dat_glyph = node_data->get_glyph();
  this->vk_engine = node_vulkan->get_vk_engine();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  utl::type::Pose* pose = entity->get_pose();
  //---------------------------

  //If object; create dedicated glyphs
  if(utl::entity::Object* object = dynamic_cast<utl::entity::Object*>(entity)){
    dat_glyph->create_glyph_object(object);
  }

  //Init entity
  dat_database->assign_UID(entity);
  dat_database->assign_UID(data);
  vk_engine->insert_data(data, pose);

  //---------------------------
}
void Entity::clear_entity(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  //----------------------------

  vk_engine->remove_data(data);

  //----------------------------
}

}
