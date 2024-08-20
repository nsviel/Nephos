#include "Model.h"

#include <Radiometry/Namespace.h>


namespace rad::cal{

//Constructor / Destructor
Model::Model(rad::cal::Node* node_calibration){
  //---------------------------

  this->rad_struct = node_calibration->get_rad_struct();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  //---------------------------



  //---------------------------
}
void Model::export_model(){
  //---------------------------

  //---------------------------
}
void Model::compute_model(){
  //---------------------------



  //---------------------------
}

//Subfunction
void Model::build_model(){
  //---------------------------



  //---------------------------
}

}
