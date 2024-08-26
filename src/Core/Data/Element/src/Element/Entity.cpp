#include "Entity.h"

#include <Data/Element/Namespace.h>
#include <Data/Attribut/Namespace.h>
#include <Vulkan/Namespace.h>


namespace dat::elm{

//Constructor / Destructor
Entity::Entity(dat::elm::Node* node_element){
  //---------------------------

  vk::Node* node_vulkan = node_element->get_node_vulkan();

  this->dat_uid = node_element->get_dat_uid();
  this->vk_data = node_vulkan->get_vk_data();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  entity->UID = dat_uid->generate_UID();
  entity->data.UID = dat_uid->generate_UID();
  entity->data.is_updated = true;

  //---------------------------
}
void Entity::remove_entity(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Data& data = entity->data;
  //----------------------------

  entity->clean();
  vk_data->remove(data);

  //Remove glyph data
  for(auto& glyph : entity->list_glyph){
    this->remove_entity(glyph);
  }

  delete entity;
  entity = nullptr;

  //----------------------------
}
void Entity::reset_pose(std::shared_ptr<dat::base::Entity> entity){
  //----------------------------

  glm::mat4 init = entity->pose.model_init;
  entity->pose = {};
  entity->pose.model = init;
  entity->pose.model_init = init;

  //----------------------------
}
void Entity::visibility_entity(std::shared_ptr<dat::base::Entity> entity, bool value){
  if(!entity) return;
  //---------------------------

  entity->data.is_visible = value;

  //Glyph visibility
  for(std::shared_ptr<dat::base::Glyph> glyph : entity->list_glyph){
    this->visibility_entity(glyph, value);
  }

  //If visible so parent set is too
  std::shared_ptr<dat::base::Set> set = entity->set_parent.lock();
  if(value && set && !set->is_visible){
    set->is_visible  = true;
  }

  //---------------------------
}
void Entity::update_data(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Data& data = entity->data;
  utl::base::Pose& pose = entity->pose;
  //----------------------------

  if(data.is_updated){
    vk_data->insert(data, pose);

    //Update attribut
    atr_location->compute_centroid(entity);

    //Update own glyph pose
    for(auto& glyph : entity->list_glyph){
      this->update_data(glyph);
    }

    data.is_updated = false;
  }

  //----------------------------
}

}
