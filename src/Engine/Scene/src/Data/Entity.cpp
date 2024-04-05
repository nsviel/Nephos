#include "Entity.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Entity::Entity(eng::scene::Node* node_scene){
  //---------------------------

  eng::Node* node_engine = node_scene->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->node_scene = node_scene;
  this->sce_database = node_scene->get_scene_database();
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
    this->sce_glyph = node_scene->get_scene_glyph();
    sce_glyph->create_glyph_object(object);
  }

  //Init entity
  sce_database->assign_UID(entity);
  sce_database->assign_UID(data);
  vk_engine->insert_data_in_engine(data, pose);

  //---------------------------
}
void Entity::clear_entity(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  //----------------------------

  vk_engine->remove_data_in_engine(data);

  //----------------------------
}

}
