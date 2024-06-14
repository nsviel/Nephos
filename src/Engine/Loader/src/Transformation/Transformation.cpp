#include "Transformation.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Transformation::Transformation(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
std::vector<std::string> Transformation::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  vec_format.push_back("json");

  //---------------------------
  return vec_format;
}

}
