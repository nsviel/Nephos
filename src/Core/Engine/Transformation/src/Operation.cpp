#include "Operation.h"

#include <Transformation/Namespace.h>
#include <Attribut/Namespace.h>


namespace eng::trf{

// Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->trf_transform = new eng::trf::Transformation();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Operation::~Operation(){}

//Operation on set
void Operation::center_object(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    atr_location->compute_MinMax(set);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      this->center_object(entity, set->pose.COM);
      this->elevate_object(entity, set->pose.min);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    utl::base::Pose* pose = &entity->pose;
    this->center_object(entity, pose->COM);
    this->elevate_object(entity, pose->min);
  }

  //---------------------------
}
void Operation::elevate_object(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    atr_location->compute_MinMax(set);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      this->elevate_object(entity, set->pose.min);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    utl::base::Pose* pose = &entity->pose;
    this->elevate_object(entity, pose->min);
  }

  //---------------------------
}
void Operation::make_rotation_X_90d(utl::base::Element* element, int value){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      this->make_rotation_X_90d(entity, value);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->make_rotation_X_90d(entity, value);
  }

  //---------------------------
}
void Operation::make_translation(utl::base::Element* element, glm::vec3 value){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    trf_transform->make_translation(&set->pose, value);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      trf_transform->make_translation(&entity->pose, value);
    }
    for(int i=0; i<set->list_subset.size(); i++){
      dat::base::Set* subset = *next(set->list_subset.begin(), i);
      this->make_translation(subset, value);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    trf_transform->make_translation(&entity->pose, value);
  }

  //---------------------------
}
void Operation::make_rotation(utl::base::Element* element, glm::vec3 COM, glm::vec3 value){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    trf_transform->make_rotation(&set->pose, COM, value);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      this->make_rotation(entity, COM, value);
    }
    for(int i=0; i<set->list_subset.size(); i++){
      dat::base::Set* subset = *next(set->list_subset.begin(), i);
      this->make_rotation(subset, COM, value);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    trf_transform->make_rotation(&entity->pose, COM, value);
  }

  //---------------------------
}

//Operation on entity
void Operation::center_object(dat::base::Entity* entity, glm::vec3 COM){
  if(entity == nullptr) return;
  //---------------------------

  utl::base::Pose* pose = &entity->pose;
  atr_location->compute_MinMax(entity);
  trf_transform->make_translation(pose, glm::vec3(-pose->COM.x, -pose->COM.y, 0));

  //---------------------------
}
void Operation::elevate_object(dat::base::Entity* entity, glm::vec3 min){
  if(entity == nullptr) return;
  //---------------------------

  utl::base::Pose* pose = &entity->pose;
  atr_location->compute_MinMax(entity);
  trf_transform->make_translation(pose, glm::vec3(0, 0, -min.z));

  //---------------------------
}
void Operation::make_rotation_X_90d(dat::base::Entity* entity, int value){
  if(entity == nullptr) return;
  //---------------------------

  utl::base::Pose* pose = &entity->pose;
  atr_location->compute_MinMax(entity);
  trf_transform->make_rotation_axe_X(pose, value * 90);
  this->elevate_object(entity, pose->min);

  //---------------------------
}
void Operation::make_translation_from_root(dat::base::Entity* entity, glm::vec3 new_root){
  if(entity == nullptr) return;
  //---------------------------

  utl::base::Pose* pose = &entity->pose;
  glm::vec3 translation = new_root - pose->root;
  trf_transform->make_translation(pose, translation);

  //---------------------------
}

}
