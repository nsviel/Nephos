#include "Model.h"

#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>

namespace rad::model::chart{

//Constructor / Destructor
Model::Model(rad::Node* node_radio){
  //---------------------------

  rad::model::Node* node_model = node_radio->get_node_model();

  this->rad_struct = node_model->get_rad_struct();

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
