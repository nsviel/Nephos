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

//Main function
void Operation::make_operation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  this->make_transformation(entity);



  //---------------------------
}

//Subfunction
void Operation::make_transformation(dat::base::Entity* entity){
  if(!ldr_struct->exporter.transformed) return;
  //---------------------------

  utl::base::Data* data = entity->data;

  for(int i=0; i<data->xyz.size(); i++){
    
  }

  //---------------------------
}

}
