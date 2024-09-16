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
  this->vk_interface = node_vulkan->get_vk_interface();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  entity->UID = dat_uid->generate_UID();
  entity->data->UID = dat_uid->generate_UID();
  entity->data->is_updated = true;

  //---------------------------
}
void Entity::remove_entity(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Data& data = *entity->data;
  //----------------------------

  entity->clean();
  vk_interface->remove_data(data);

  //Remove glyph data
  for(auto& glyph : entity->list_glyph){
    this->remove_entity(glyph);
  }

  //----------------------------
}
void Entity::reset_pose(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Pose& pose = *entity->pose;
  //----------------------------

  glm::mat4 init = pose.model_init;
  pose = {};
  pose.model = init;
  pose.model_init = init;

  //----------------------------
}
void Entity::visibility_entity(std::shared_ptr<dat::base::Entity> entity, bool value){
  if(!entity) return;
  //---------------------------

  entity->data->is_visible = value;

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
  //----------------------------

  if(entity->data->is_updated){
    vk_interface->insert_data(entity->data, entity->pose);

    //Update attribut
    atr_location->compute_centroid(*entity);

    //Update own glyph pose
    for(auto& glyph : entity->list_glyph){
      this->update_data(glyph);
    }

    entity->data->is_updated = false;
  }

  //----------------------------
}

}
