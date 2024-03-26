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

  float& resolution = k4n_struct->matching.model.resolution;
  float& min_R = k4n_struct->matching.model.min_R;
  float& max_R = k4n_struct->matching.model.max_R;
  int nb_element = static_cast<int>((max_R - min_R) / resolution) + 1;
  k4n_struct->matching.model.vec_I = vector<float>(nb_element, 0.0f);
  k4n_struct->matching.model.vec_R = vector<float>(nb_element, 0.0f);

  float It_resolution = 1;
  float It_min = 0;
  float It_max = 90;
  int It_nb = static_cast<int>((It_max - It_min) / It_resolution) + 1;
  k4n_struct->matching.model.vec_I_It = vector<float>(It_nb, 0.0f);
  k4n_struct->matching.model.vec_It = vector<float>(It_nb, 0.0f);

  //---------------------------
}

//Subfunction
void Model::add_element(){
  //---------------------------




  //---------------------------
}


}
