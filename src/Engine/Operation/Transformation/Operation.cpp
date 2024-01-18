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

//Main function
void Operation::center_object(utl::type::Entity* entity){
  if(entity == nullptr) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  ope_attribut->compute_MinMax(entity);
  ope_transform->make_translation(entity, vec3(-data->COM.x, -data->COM.y, -data->min.z));

  //---------------------------
}
void Operation::elevate_object(utl::type::Entity* entity){
  if(entity == nullptr) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  ope_attribut->compute_MinMax(entity);
  ope_transform->make_translation(entity, vec3(0, 0, -data->min.z));

  //---------------------------
}
void Operation::make_rotation_X_90d(utl::type::Entity* entity, int value){
  if(entity == nullptr) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  ope_attribut->compute_MinMax(entity);
  ope_transform->make_rotation_axe_X(entity, value * 90);
  this->elevate_object(entity);

  //---------------------------
}

}
