#include "Model.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  //---------------------------
  this->init_model();
}
Model::~Model(){}

//Main function
void Model::init_model(){
  //---------------------------

  float& resolution = k4n_struct->matching.model.resolution;
  float& max_R = k4n_struct->matching.model.max_R;
  float& min_R = k4n_struct->matching.model.min_R;
  int nb_element = static_cast<int>((max_R - min_R) / resolution) + 1;
  k4n_struct->matching.model.vec_I = vector<float>(nb_element, 0.0f);
  k4n_struct->matching.model.vec_R = vector<float>(nb_element, 0.0f);


  //---------------------------
}

//Subfunction




}
