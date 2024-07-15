#include "Operation.h"

#include <IO/Namespace.h>
#include <Utility/Namespace.h>


namespace io::exporter{

//Constructor / Destructor
Operation::Operation(io::Node* node_io){
  //---------------------------

  this->io_struct = node_io->get_io_struct();

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
  if(!io_struct->exporter.with_transformation) return;
  //---------------------------

  utl::base::Data* data = &entity->data;

  for(int i=0; i<data->xyz.size(); i++){
    //glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * pose->model;
    //file << std::setprecision(precision) << xyzw.x <<" "<< xyzw.y <<" "<< xyzw.z <<" ";
  }

  //---------------------------
}

}
