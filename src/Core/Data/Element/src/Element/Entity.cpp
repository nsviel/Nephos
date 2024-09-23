#include "Entity.h"

#include <Data/Element/Namespace.h>
#include <Data/Attribut/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


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
void Entity::init_entity(dat::base::Entity& entity){
  //---------------------------

  entity.UID = dat_uid->generate_UID();
  entity.data->UID = dat_uid->generate_UID();
  entity.data->is_updated = true;
  vk_data->insert_data(entity.data, entity.pose);

  //---------------------------
}
void Entity::remove_entity(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  //----------------------------

  entity.clean();
  vk_data->remove_data(data);

  //Remove glyph data
  for(auto& glyph : entity.list_glyph){
    this->remove_entity(*glyph);
  }

  //----------------------------
}
void Entity::reset_pose(dat::base::Entity& entity){
  utl::base::Pose& pose = *entity.pose;
  //----------------------------

  glm::mat4 init = pose.initial;
  pose = {};
  pose.model = init;
  pose.initial = init;

  //----------------------------
}
void Entity::visibility_entity(dat::base::Entity& entity, bool value){
  //---------------------------

  entity.data->is_visible = value;

  //Glyph visibility
  for(auto& glyph : entity.list_glyph){
    this->visibility_entity(*glyph, value);
  }

  //If visible so parent set is too
  std::shared_ptr<dat::base::Set> set = entity.set_parent.lock();
  if(value && set && !set->is_visible){
    set->is_visible  = true;
  }

  //---------------------------
}
void Entity::update_data(dat::base::Entity& entity){
  //----------------------------

  if(entity.data->is_updated){
    vk_data->insert_data(entity.data, entity.pose);

    //Update attribut
    atr_location->compute_centroid(entity);

    //Update own glyph pose
    for(auto& glyph : entity.list_glyph){
      this->update_data(*glyph);
    }

    entity.data->is_updated = false;
  }

  //----------------------------
}

}
