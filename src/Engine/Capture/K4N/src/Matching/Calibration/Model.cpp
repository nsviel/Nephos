#include "Model.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  //---------------------------
  this->init();
}
Model::~Model(){}

//Main function
void Model::init(){
  //---------------------------

  //I(R)
  float& IfR_resolution = k4n_struct->matching.model.IfR.x_resolution;
  float& IfR_min_R = k4n_struct->matching.model.IfR.x_min;
  float& IfR_max_R = k4n_struct->matching.model.IfR.x_max;

  IfR_resolution = 0.01f;
  IfR_min_R = 0.0f;
  IfR_max_R = 3.0f;

  int IfR_nb_element = static_cast<int>((IfR_max_R - IfR_min_R) / IfR_resolution) + 1;
  k4n_struct->matching.model.IfR.vec_x = vector<float>(IfR_nb_element, 0.0f);
  k4n_struct->matching.model.IfR.vec_y = vector<float>(IfR_nb_element, 0.0f);

  //I(It)
  float& IfIt_resolution = k4n_struct->matching.model.IfIt.x_resolution;
  float& IfIt_min_It = k4n_struct->matching.model.IfIt.x_min;
  float& IfIt_max_It = k4n_struct->matching.model.IfIt.x_max;

  IfIt_resolution = 1.0f;
  IfIt_min_It = 0.0f;
  IfIt_max_It = 90.0f;

  int IfIt_nb_element = static_cast<int>((IfIt_max_It - IfIt_min_It) / IfIt_resolution) + 1;
  k4n_struct->matching.model.IfIt.vec_x = vector<float>(IfIt_nb_element, 0.0f);
  k4n_struct->matching.model.IfIt.vec_y = vector<float>(IfIt_nb_element, 0.0f);

  //---------------------------
}

//Subfunction
void Model::add_element(){
  //---------------------------




  //---------------------------
}


}
