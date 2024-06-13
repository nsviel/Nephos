#include "Operation.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::exporter{

//Constructor / Destructor
Operation::Operation(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  //---------------------------
}
Operation::~Operation(){}

//Main functions
void Operation::make_operation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------


  //---------------------------
}

}
