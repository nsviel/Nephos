#include "Operation.h"

#include <Operation/Namespace.h>


namespace ope{

// Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->ope_transform = new ope::Transformation();
  this->ope_location = new ope::attribut::Location();

  //---------------------------
}
Operation::~Operation(){}

//Operation on set
void Operation::center_object(utl::type::Set* set){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    ope_location->compute_MinMax(set);
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      this->center_object(entity, set->pose.COM);
      this->elevate_object(entity, set->pose.min);
    }
  }else{
    utl::type::Entity* entity = set->selected_entity;
    this->center_object(entity, entity->get_pose()->COM);
    this->elevate_object(entity, entity->get_pose()->min);
  }

  //---------------------------
}
void Operation::elevate_object(utl::type::Set* set){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    ope_location->compute_MinMax(set);
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      this->elevate_object(entity, set->pose.min);
    }
  }else{
    utl::type::Entity* entity = set->selected_entity;
    this->elevate_object(entity, entity->get_pose()->min);
  }

  //---------------------------
}
void Operation::make_rotation_X_90d(utl::type::Set* set, int value){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      this->make_rotation_X_90d(entity, value);
    }
  }else{
    this->make_rotation_X_90d(set->selected_entity, value);
  }

  //---------------------------
}
void Operation::make_translation(utl::type::Set* set, vec3 value){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      ope_transform->make_translation(entity, value);
    }
  }else{
    ope_transform->make_translation(set->selected_entity, value);
  }

  //---------------------------
}
void Operation::make_rotation(utl::type::Set* set, vec3 value){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    vec3 COM = ope_location->compute_centroid(set);
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      ope_transform->make_rotation(entity, COM, value);
    }
  }else{
    ope_transform->make_rotation(set->selected_entity, value);
  }

  //---------------------------
}

//Operation on entity
void Operation::center_object(utl::type::Entity* entity, vec3 COM){
  if(entity == nullptr || !entity->is_movable) return;
  utl::type::Pose* pose = entity->get_pose();
  //---------------------------

  ope_location->compute_MinMax(entity);
  ope_transform->make_translation(entity, vec3(-pose->COM.x, -pose->COM.y, 0));

  //---------------------------
}
void Operation::elevate_object(utl::type::Entity* entity, vec3 min){
  if(entity == nullptr || !entity->is_movable) return;
  //---------------------------

  ope_location->compute_MinMax(entity);
  ope_transform->make_translation(entity, vec3(0, 0, -min.z));

  //---------------------------
}
void Operation::make_rotation_X_90d(utl::type::Entity* entity, int value){
  if(entity == nullptr || !entity->is_movable) return;
  utl::type::Pose* pose = entity->get_pose();
  //---------------------------

  ope_location->compute_MinMax(entity);
  ope_transform->make_rotation_axe_X(entity, value * 90);
  this->elevate_object(entity, pose->min);

  //---------------------------
}
void Operation::make_translation_from_root(utl::type::Entity* entity, vec3 new_root){
  if(entity == nullptr) return;
  //---------------------------

  vec3 translation = new_root - entity->get_pose()->root;
  ope_transform->make_translation(entity, translation);

  //---------------------------
}

}
