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
void Operation::center_object(entity::Object* object){
  //---------------------------

  ope_attribut->compute_MinMax(object);
  ope_transform->make_translation(object, vec3(-object->data->COM.x, -object->data->COM.y, -object->data->min.z));

  //---------------------------
}
void Operation::elevate_object(entity::Object* object){
  //---------------------------

  ope_attribut->compute_MinMax(object);
  ope_transform->make_translation(object, vec3(0, 0, -object->data->min.z));

  //---------------------------
}

}
