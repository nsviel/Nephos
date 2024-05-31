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

  //Init entity glyphes
  for(int i=0; i<entity->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);
    this->init_entity(glyph);
  }

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

  //----------------------------
}
void Entity::reset_entity(dat::base::Entity* entity){
  utl::base::Pose* pose = &entity->pose;;
  //----------------------------

  pose->min = glm::vec3(0.0f);
  pose->max = glm::vec3(0.0f);
  pose->root = glm::vec3(0.0f);
  pose->COM = glm::vec3(0.0f);

  pose->rotat = glm::mat4(1.0f);
  pose->trans = glm::mat4(1.0f);
  pose->scale = glm::mat4(1.0f);
  pose->model = pose->model_init;
  pose->mvp = glm::mat4(1.0f);

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
