#include "Entity.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Camera/Namespace.h>


namespace dat{

//Constructor / Destructor
Entity::Entity(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  cam::Node* node_camera = node_engine->get_node_camera();

  this->node_engine = node_engine;
  this->cam_control = node_camera->get_cam_control();
  this->dat_struct = node_data->get_dat_struct();
  this->vk_engine = node_vulkan->get_vk_engine();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;;
  //---------------------------

  //Init entity
  entity->UID = dat_struct->UID++;
  data->UID = dat_struct->UID++;
  this->update_pose(entity);
  this->update_data(entity);

  //---------------------------
}
void Entity::remove_entity(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //----------------------------

  entity->clean();
  vk_engine->remove_data(data);

  //Remove glyph data
  for(int i=0; i<entity->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);
    this->remove_entity(glyph);
  }

  delete entity;
  entity = nullptr;

  //----------------------------
}
void Entity::reset_pose(dat::base::Entity* entity){
  //----------------------------

  glm::mat4 init = entity->pose.model_init;
  entity->pose = {};
  entity->pose.model = init;
  entity->pose.model_init = init;

  //----------------------------
}
void Entity::visibility_entity(dat::base::Entity* entity, bool value){
  utl::base::Data* data = &entity->data;
  //---------------------------

  data->is_visible = value;

  //Glyph visibility
  for(int i=0; i<entity->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);
    this->visibility_entity(glyph, value);
  }

  //---------------------------
}
void Entity::update_data(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;;
  //----------------------------

  vk_engine->insert_data(data, pose);

  //----------------------------
}
void Entity::update_pose(dat::base::Entity* entity){
  utl::base::Pose* pose = &entity->pose;;
  //----------------------------

  //Update own pose
  cam_control->compute_camera_mvp(pose);

  //Update own glyph pose
  for(int i=0; i<entity->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);
    glyph->update_pose(entity);
    this->update_pose(glyph);
  }

  //----------------------------
}

}
