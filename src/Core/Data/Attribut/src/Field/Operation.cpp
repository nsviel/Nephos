#include "Operation.h"

#include <Data/Attribut/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::atr::field{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->atr_field = new dat::atr::field::Manager();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::normalize_field(utl::base::Data& data, const std::string& name){
  //---------------------------

  std::vector<float>& vec_field = atr_field->get_field_data(data, name);
  math::normalize(vec_field);

  //---------------------------
}

}
