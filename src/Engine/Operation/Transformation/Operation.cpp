#include "Operation.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>


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
void Operation::center_object(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    ope_location->compute_MinMax(set);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      this->center_object(entity, set->pose.COM);
      this->elevate_object(entity, set->pose.min);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->center_object(entity, entity->get_pose()->COM);
    this->elevate_object(entity, entity->get_pose()->min);
  }

  //---------------------------
}
void Operation::elevate_object(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    ope_location->compute_MinMax(set);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      this->elevate_object(entity, set->pose.min);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->elevate_object(entity, entity->get_pose()->min);
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
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      ope_transform->make_translation(entity, value);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    ope_transform->make_translation(entity, value);
  }

  //---------------------------
}
void Operation::make_rotation(utl::base::Element* element, glm::vec3 value){
  if(element == nullptr) return;
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    glm::vec3 COM = ope_location->compute_centroid(set);
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      ope_transform->make_rotation(entity, COM, value);
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    ope_transform->make_rotation(entity, value);
  }

  //---------------------------
}

//Operation on entity
void Operation::center_object(dat::base::Entity* entity, glm::vec3 COM){
  if(entity == nullptr || !entity->is_movable) return;
  utl::base::Pose* pose = entity->get_pose();
  //---------------------------

  ope_location->compute_MinMax(entity);
  ope_transform->make_translation(entity, glm::vec3(-pose->COM.x, -pose->COM.y, 0));

  //---------------------------
}
void Operation::elevate_object(dat::base::Entity* entity, glm::vec3 min){
  if(entity == nullptr || !entity->is_movable) return;
  //---------------------------

  ope_location->compute_MinMax(entity);
  ope_transform->make_translation(entity, glm::vec3(0, 0, -min.z));

  //---------------------------
}
void Operation::make_rotation_X_90d(dat::base::Entity* entity, int value){
  if(entity == nullptr || !entity->is_movable) return;
  utl::base::Pose* pose = entity->get_pose();
  //---------------------------

  ope_location->compute_MinMax(entity);
  ope_transform->make_rotation_axe_X(entity, value * 90);
  this->elevate_object(entity, pose->min);

  //---------------------------
}
void Operation::make_translation_from_root(dat::base::Entity* entity, glm::vec3 new_root){
  if(entity == nullptr) return;
  //---------------------------

  glm::vec3 translation = new_root - entity->get_pose()->root;
  ope_transform->make_translation(entity, translation);

  //---------------------------
}

}
