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
void Operation::center_object(eng::data::Object* object){
  //---------------------------

  ope_attribut->compute_MinMax(object);
  ope_transform->make_translation(object, vec3(-object->COM.x, -object->COM.y, -object->min.z));

  //---------------------------
}
void Operation::elevate_object(eng::data::Object* object){
  //---------------------------

  ope_attribut->compute_MinMax(object);
  ope_transform->make_translation(object, vec3(0, 0, -object->min.z));

  //---------------------------
}

}
