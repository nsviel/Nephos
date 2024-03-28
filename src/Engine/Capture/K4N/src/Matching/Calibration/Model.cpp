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
  plot_ifr->x.resolution = 0.01f;
  plot_ifr->x.min = 0.0f;
  plot_ifr->x.max = 5.0f;
  plot_ifr->x.size = static_cast<int>((plot_ifr->x.max - plot_ifr->x.min) / plot_ifr->x.resolution) + 1;
  plot_ifr->x.data = vector<float>(plot_ifr->x.size, 0.0f);
  plot_ifr->y.data = vector<float>(plot_ifr->x.size, 0.0f);

  //I(It)
  utl::type::Plot* plot_ifit = &k4n_struct->matching.model.IfIt;
  plot_ifit->title = "I(It)";
  plot_ifit->x.resolution = 1.0f;
  plot_ifit->x.min = 0.0f;
  plot_ifit->x.max = 90.0f;
  plot_ifit->x.size = static_cast<int>((plot_ifit->x.max - plot_ifit->x.min) / plot_ifit->x.resolution) + 1;
  plot_ifit->x.data = vector<float>(plot_ifit->x.size, 0.0f);
  plot_ifit->y.data = vector<float>(plot_ifit->x.size, 0.0f);

  //I(R, It)
  utl::type::Plot* plot_ifrit = &k4n_struct->matching.model.IfRIt;
  plot_ifrit->title = "I(R, It)";

  plot_ifrit->x.resolution = 0.01f;
  plot_ifrit->x.min = 0.0f;
  plot_ifrit->x.max = 5.0f;
  plot_ifrit->x.size = static_cast<int>((plot_ifrit->x.max - plot_ifrit->x.min) / plot_ifrit->x.resolution) + 1;

  plot_ifrit->y.resolution = 1.0f;
  plot_ifrit->y.min = 0.0f;
  plot_ifrit->y.max = 90.0f;
  plot_ifrit->y.size = static_cast<int>((plot_ifrit->y.max - plot_ifrit->y.min) / plot_ifrit->y.resolution) + 1;

  plot_ifrit->z.min = 0.0f;
  plot_ifrit->z.max = 2500.0f;
  plot_ifrit->z.size = plot_ifrit->x.size * plot_ifrit->y.size;
  plot_ifrit->z.data = vector<float>(plot_ifrit->z.size, 0.0f);

  //Model
  k4n_struct->matching.model.vec_data = vector<vec3>(plot_ifrit->z.size, vec3(-1, -1, -1));
  k4n_struct->matching.model.min_R = 1000;
  k4n_struct->matching.model.max_R = -1;

  //---------------------------
}

//Subfunction
void Model::export_model(){
  //---------------------------

  utl::file::write_vector(k4n_struct->matching.model.path, k4n_struct->matching.model.vec_data);

  //---------------------------
}
void Model::import_model(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  //Import file model data
  model->vec_data = utl::file::read_vector(model->path);

  //Fill model plot data
  for(int i=0; i<model->vec_data.size(); i++){
    float& R = model->vec_data[i].x;
    float& It = model->vec_data[i].y;
    float& I = model->vec_data[i].z;

    model->IfRIt.z.data[i] = I;

    //Search for R limite validity
    if(R > model->max_R) model->max_R = R;
    if(R < model->min_R && R != -1) model->min_R = R;

    //I(It)
    if(It < 5 && It > 0){
      int index = static_cast<int>(std::round(R / model->IfR.x.resolution));
      model->IfR.x.data[index] = R;
      model->IfR.y.data[index] = I;
    }
  }

  //---------------------------
}
void Model::make_model(){
  //---------------------------

  ope_polyfit->compute(k4n_struct->matching.model.vec_data, k4n_struct->matching.model.degree);

  //---------------------------
}
float Model::apply_model(float x, float y){
  //---------------------------

  float z = ope_polyfit->evaluate(x, y);

  if(z < 0) z = 0;

  //---------------------------
  return z;
}


}
