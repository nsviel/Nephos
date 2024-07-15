#include "Entity.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Camera/Namespace.h>


namespace dat::element{

//Constructor / Destructor
Entity::Entity(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->node_engine = node_engine;
  this->dat_struct = node_data->get_dat_struct();
  this->dat_uid = node_data->get_dat_uid();

  this->vk_data = node_vulkan->get_vk_data();
  this->ope_location = new ope::attribut::Location();
  this->ope_attribut = new ope::attribut::Attribut();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::init_entity(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;;
  //---------------------------

  //Init entity
  entity->UID = dat_uid->generate_UID();
  data->UID = dat_uid->generate_UID();
  this->update_pose(entity);
  this->update_data(entity);

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

  vk_data->insert(data, pose);

  //Update attribut
  ope_location->compute_centroid(entity);
  //ope_attribut->compute_range(entity);

  //----------------------------
}
void Entity::update_pose(dat::base::Entity* entity){
  utl::base::Pose* pose = &entity->pose;;
  //----------------------------

  cam::Node* node_camera = node_engine->get_node_camera();
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
