#include "Operation.h"


namespace eng::ope{

// Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->ope_transform = new eng::ope::Transformation();
  this->ope_attribut = new eng::ope::Attribut();

  //---------------------------
}
Operation::~Operation(){}

//Operation on set
void Operation::center_object(utl::type::Set* set){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      this->center_object(entity);
    }
  }else{
    this->center_object(set->selected_entity);
  }

  //---------------------------
}
void Operation::elevate_object(utl::type::Set* set){
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      this->elevate_object(entity);
    }
  }else{
    this->elevate_object(set->selected_entity);
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
    for(int i=0; i<set->list_entity.size(); i++){
      utl::type::Entity* entity = *next(set->list_entity.begin(), i);
      ope_transform->make_rotation(entity, value);
    }
  }else{
    ope_transform->make_rotation(set->selected_entity, value);
  }

  //---------------------------
}

//Operation on entity
void Operation::center_object(utl::type::Entity* entity){
  if(entity == nullptr || !entity->is_movable) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  ope_attribut->compute_MinMax(entity);
  ope_transform->make_translation(entity, vec3(-data->COM.x, -data->COM.y, -data->min.z));

  //---------------------------
}
void Operation::elevate_object(utl::type::Entity* entity){
  if(entity == nullptr || !entity->is_movable) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  ope_attribut->compute_MinMax(entity);
  ope_transform->make_translation(entity, vec3(0, 0, -data->min.z));

  //---------------------------
}
void Operation::make_rotation_X_90d(utl::type::Entity* entity, int value){
  if(entity == nullptr || !entity->is_movable) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  ope_attribut->compute_MinMax(entity);
  ope_transform->make_rotation_axe_X(entity, value * 90);
  this->elevate_object(entity);

  //---------------------------
}

}
