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
  utl::type::Plot* plot_ifr = &k4n_struct->matching.model.IfR;
  plot_ifr->title = "I(R)";
  plot_ifr->x_resolution = 0.01f;
  plot_ifr->x_min = 0.0f;
  plot_ifr->x_max = 3.0f;
  plot_ifr->size = static_cast<int>((plot_ifr->x_max - plot_ifr->x_min) / plot_ifr->x_resolution) + 1;
  plot_ifr->vec_x = vector<float>(plot_ifr->size, 0.0f);
  plot_ifr->vec_y = vector<float>(plot_ifr->size, 0.0f);

  //I(It)
  utl::type::Plot* plot_ifit = &k4n_struct->matching.model.IfIt;
  plot_ifit->title = "I(It)";
  plot_ifit->x_resolution = 1.0f;
  plot_ifit->x_min = 0.0f;
  plot_ifit->x_max = 90.0f;
  plot_ifit->size = static_cast<int>((plot_ifit->x_max - plot_ifit->x_min) / plot_ifit->x_resolution) + 1;
  plot_ifit->vec_x = vector<float>(plot_ifit->size, 0.0f);
  plot_ifit->vec_y = vector<float>(plot_ifit->size, 0.0f);

  //---------------------------
}

//Subfunction
void Model::add_element(){
  //---------------------------




  //---------------------------
}


}
