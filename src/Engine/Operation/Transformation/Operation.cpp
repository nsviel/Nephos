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
void Operation::center_object(utl::base::Data* data){
  //---------------------------

  ope_attribut->compute_MinMax(data);
  ope_transform->make_translation(data, vec3(-data->COM.x, -data->COM.y, -data->min.z));

  //---------------------------
}
void Operation::elevate_object(utl::base::Data* data){
  //---------------------------

  ope_attribut->compute_MinMax(data);
  ope_transform->make_translation(data, vec3(0, 0, -data->min.z));

  //---------------------------
}

}
