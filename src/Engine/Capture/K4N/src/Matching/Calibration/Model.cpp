#include "Model.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::determine_model(k4n::dev::Sensor* sensor){
  //---------------------------


  //---------------------------
}

//Subfunction




}
