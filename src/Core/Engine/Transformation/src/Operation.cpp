#include "Operation.h"

#include <Engine/Transformation/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


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
void Operation::center_object(std::shared_ptr<utl::base::Element> element){
  if(!element) return;
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
    atr_location->compute_MinMax(set);
    for(auto& entity : set->list_entity){
      this->center_object(entity, set->pose.COM);
      this->elevate_object(entity, set->pose.min);
    }
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    utl::base::Pose& pose = entity->pose;
    this->center_object(entity, pose.COM);
    this->elevate_object(entity, pose.min);
  }

  //---------------------------
}
void Operation::elevate_object(std::shared_ptr<utl::base::Element> element){
  if(!element) return;
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
    atr_location->compute_MinMax(set);
    for(auto& entity : set->list_entity){
      this->elevate_object(entity, set->pose.min);
    }
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    utl::base::Pose& pose = entity->pose;
    this->elevate_object(entity, pose.min);
  }

  //---------------------------
}
void Operation::make_rotation_X_90d(std::shared_ptr<utl::base::Element> element, int value){
  if(!element) return;
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
    for(auto& entity : set->list_entity){
      this->make_rotation_X_90d(entity, value);
    }
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    this->make_rotation_X_90d(entity, value);
  }

  //---------------------------
}
void Operation::make_translation(std::shared_ptr<utl::base::Element> element, glm::vec3 value){
  if(!element) return;
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
    trf_transform->make_translation(set->pose, value);
    for(auto& entity : set->list_entity){
      trf_transform->make_translation(entity->pose, value);
    }
    for(auto& subset : set->list_subset){
      this->make_translation(subset, value);
    }
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    trf_transform->make_translation(entity->pose, value);
  }

  //---------------------------
}
void Operation::make_rotation(std::shared_ptr<utl::base::Element> element, glm::vec3 COM, glm::vec3 value){
  if(!element) return;
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
    trf_transform->make_rotation(set->pose, COM, value);
    for(auto& entity : set->list_entity){
      this->make_rotation(entity, COM, value);
    }
    for(auto& subset : set->list_subset){
      this->make_rotation(subset, COM, value);
    }
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    trf_transform->make_rotation(entity->pose, COM, value);
  }

  //---------------------------
}

//Operation on entity
void Operation::center_object(std::shared_ptr<dat::base::Entity> entity, glm::vec3 COM){
  if(!entity) return;
  //---------------------------

  utl::base::Pose& pose = entity->pose;
  atr_location->compute_MinMax(*entity);
  trf_transform->make_translation(pose, glm::vec3(-pose.COM.x, -pose.COM.y, 0));

  //---------------------------
}
void Operation::elevate_object(std::shared_ptr<dat::base::Entity> entity, glm::vec3 min){
  if(!entity) return;
  //---------------------------

  utl::base::Pose& pose = entity->pose;
  atr_location->compute_MinMax(*entity);
  trf_transform->make_translation(pose, glm::vec3(0, 0, -min.z));

  //---------------------------
}
void Operation::make_rotation_X_90d(std::shared_ptr<dat::base::Entity> entity, int value){
  if(!entity) return;
  //---------------------------

  utl::base::Pose& pose = entity->pose;
  atr_location->compute_MinMax(*entity);
  trf_transform->make_rotation_axe_X(pose, value * 90);
  this->elevate_object(entity, pose.min);

  //---------------------------
}
void Operation::make_translation_from_root(std::shared_ptr<dat::base::Entity> entity, glm::vec3 new_root){
  if(!entity) return;
  //---------------------------

  utl::base::Pose& pose = entity->pose;
  glm::vec3 translation = new_root - pose.root;
  trf_transform->make_translation(pose, translation);

  //---------------------------
}

}
