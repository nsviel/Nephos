#include "Model.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->ope_polyfit = new ope::fitting::Polyfit();

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
  plot_ifr->x_max = 5.0f;
  plot_ifr->x_size = static_cast<int>((plot_ifr->x_max - plot_ifr->x_min) / plot_ifr->x_resolution) + 1;
  plot_ifr->vec_x = vector<float>(plot_ifr->x_size, 0.0f);
  plot_ifr->vec_y = vector<float>(plot_ifr->x_size, 0.0f);

  //I(It)
  utl::type::Plot* plot_ifit = &k4n_struct->matching.model.IfIt;
  plot_ifit->title = "I(It)";
  plot_ifit->x_resolution = 1.0f;
  plot_ifit->x_min = 0.0f;
  plot_ifit->x_max = 90.0f;
  plot_ifit->x_size = static_cast<int>((plot_ifit->x_max - plot_ifit->x_min) / plot_ifit->x_resolution) + 1;
  plot_ifit->vec_x = vector<float>(plot_ifit->x_size, 0.0f);
  plot_ifit->vec_y = vector<float>(plot_ifit->x_size, 0.0f);

  //I(R, It)
  utl::type::Plot* plot_ifrit = &k4n_struct->matching.model.IfRIt;
  plot_ifrit->title = "I(R, It)";

  plot_ifrit->x_resolution = 0.01f;
  plot_ifrit->x_min = 0.0f;
  plot_ifrit->x_max = 5.0f;
  plot_ifrit->x_size = static_cast<int>((plot_ifrit->x_max - plot_ifrit->x_min) / plot_ifrit->x_resolution) + 1;

  plot_ifrit->y_resolution = 1.0f;
  plot_ifrit->y_min = 0.0f;
  plot_ifrit->y_max = 90.0f;
  plot_ifrit->y_size = static_cast<int>((plot_ifrit->y_max - plot_ifrit->y_min) / plot_ifrit->y_resolution) + 1;

  plot_ifrit->z_min = 0.0f;
  plot_ifrit->z_max = 2500.0f;
  plot_ifrit->z_size = plot_ifrit->x_size * plot_ifrit->y_size;
  plot_ifrit->vec_z = vector<float>(plot_ifrit->z_size, 0.0f);

  //Model
  k4n_struct->matching.model.vec_data = vector<vec3>(plot_ifrit->z_size, vec3(-1, -1, -1));

  //---------------------------
}

//Subfunction
void Model::make_model(){
  //---------------------------

  ope_polyfit->compute(k4n_struct->matching.model.vec_data, k4n_struct->matching.model.degree);

  //---------------------------
}
float Model::apply_model(float x, float y){
  //---------------------------

  float z = ope_polyfit->evaluate(x, y);

  //---------------------------
  return z;
}


}
