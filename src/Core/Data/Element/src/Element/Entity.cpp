#include "Entity.h"

#include <Core/Namespace.h>
#include <Operation/Namespace.h>
#include <Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Camera/Namespace.h>


namespace dat::elm{

//Constructor / Destructor
Entity::Entity(dat::elm::Node* node_element){
  //---------------------------

  core::Node* node_core = node_element->get_node_core();
  vk::Node* node_vulkan = node_core->get_node_vulkan();

  this->node_core = node_core;
  this->dat_struct = node_element->get_dat_struct();
  this->dat_uid = node_element->get_dat_uid();

  this->vk_data = node_vulkan->get_vk_data();
  this->ope_location = new ope::attribut::Location();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(dat::base::Entity* entity){
  //---------------------------

  //Init entity
  entity->UID = dat_uid->generate_UID();
  entity->data.UID = dat_uid->generate_UID();
  entity->data.is_updated = true;

  //Init sensor
  //if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
  //  dyn_sensor->init_sensor(sensor);
  //}

  //---------------------------
}
void Entity::remove_entity(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //----------------------------

  entity->clean();
  vk_data->remove(data);

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
  if(!entity) return;
  //---------------------------

  entity->data.is_visible = value;

  //Glyph visibility
  for(dat::base::Glyph* glyph : entity->list_glyph){
    this->visibility_entity(glyph, value);
  }

  //If visible so parent set is too
  dat::base::Set* set = entity->set_parent;
  if(value && set && !set->is_visible){
    set->is_visible  = true;
  }

  //---------------------------
}
void Entity::update_data(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;;
  //----------------------------

  if(data->is_updated){
    vk_data->insert(data, pose);

    //Update attribut
    ope_location->compute_centroid(entity);

    //Update own glyph pose
    for(int i=0; i<entity->list_glyph.size(); i++){
      dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);
      this->update_data(glyph);
    }

    data->is_updated = false;
  }

  //----------------------------
}
void Entity::update_pose(dat::base::Entity* entity){
  utl::base::Pose* pose = &entity->pose;
  //----------------------------

  cam::Node* node_camera = node_core->get_node_camera();
  this->cam_control = node_camera->get_cam_control();

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
