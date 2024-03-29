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
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  //I(R)
  model->IfR.title = "I(R)";
  model->IfR.x.resolution = 0.01f;
  model->IfR.x.min = 0.0f;
  model->IfR.x.max = 5.0f;
  model->IfR.x.size = static_cast<int>((model->IfR.x.max - model->IfR.x.min) / model->IfR.x.resolution) + 1;
  model->IfR.x.data = vector<float>(model->IfR.x.size, 0.0f);
  model->IfR.y.data = vector<float>(model->IfR.x.size, 0.0f);

  //I(It)
  model->IfIt.title = "I(It)";
  model->IfIt.x.resolution = 1.0f;
  model->IfIt.x.min = 0.0f;
  model->IfIt.x.max = 90.0f;
  model->IfIt.x.size = static_cast<int>((model->IfIt.x.max - model->IfIt.x.min) / model->IfIt.x.resolution) + 1;
  model->IfIt.x.data = vector<float>(model->IfIt.x.size, 0.0f);
  model->IfIt.y.data = vector<float>(model->IfIt.x.size, 0.0f);

  //I(R, It)
  model->IfRIt.title = "I(R, It)";
  model->IfRIt.x.resolution = 0.01f;
  model->IfRIt.x.min = 0.0f;
  model->IfRIt.x.max = 5.0f;
  model->IfRIt.x.size = static_cast<int>((model->IfRIt.x.max - model->IfRIt.x.min) / model->IfRIt.x.resolution) + 1;
  model->IfRIt.y.resolution = 1.0f;
  model->IfRIt.y.min = 0.0f;
  model->IfRIt.y.max = 90.0f;
  model->IfRIt.y.size = static_cast<int>((model->IfRIt.y.max - model->IfRIt.y.min) / model->IfRIt.y.resolution) + 1;
  model->IfRIt.z.min = 0.0f;
  model->IfRIt.z.max = 2500.0f;
  model->IfRIt.z.size = model->IfRIt.x.size * model->IfRIt.y.size;
  model->IfRIt.z.data = vector<float>(model->IfRIt.z.size, 0.0f);

  //Model
  model->vec_data = vector<vec3>(model->IfRIt.z.size, vec3(-1, -1, -1));
  model->x.bound = vec2(1000, -1);
  model->x.current = 0;
  model->y.bound = vec2(0, 90);
  model->y.current = 40;

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
  this->update_plot();

  //---------------------------
}
void Model::update_plot(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  //Fill model plot data
  for(int i=0; i<model->vec_data.size(); i++){
    float& R = model->vec_data[i].x;
    float& It = model->vec_data[i].y;
    float& I = model->vec_data[i].z;
    if(R == -1) continue;

    model->IfRIt.z.data[i] = I;

    //Search for R limite validity
    if(R < model->x.bound[0]) model->x.bound[0] = R;
    if(R > model->x.bound[1]) model->x.bound[1] = R;

    //I(R)
    if(It > model->y.current && It < model->y.current + 5){
      int index = static_cast<int>(std::round(R / model->IfR.x.resolution));
      model->IfR.x.data[index] = R;
      model->IfR.y.data[index] = I;

      if(R > model->x.current && R < model->x.current + 0.05){
        model->IfR.highlight = vec2(R, I);
      }
    }

    //I(It)
    if(R > model->x.current && R < model->x.current + 0.05){
      int index = static_cast<int>(std::round(It / model->IfIt.x.resolution));
      model->IfIt.x.data[index] = It;
      model->IfIt.y.data[index] = I;
    }
  }

  //---------------------------
}
void Model::make_model(){
  //---------------------------

  ope_polyfit->compute(k4n_struct->matching.model.vec_data, k4n_struct->matching.model.degree);


/*
potential fitting systems
Local Regression (LOESS/LOWESS):
    LOESS (Locally Weighted Scatterplot Smoothing) and LOWESS (Locally Weighted Scatterplot Smoothing) are non-parametric regression methods that fit smooth curves to data by locally fitting a polynomial regression model.
    These methods use a moving window to fit regression models to subsets of the data, with weights assigned based on the distance of each point from the point being estimated.
    LOESS and LOWESS can capture local variations in the data well and provide flexible surface fitting without assuming a specific global function form.

Kernel Smoothing:
    Kernel smoothing methods estimate the underlying surface by averaging nearby data points, weighted by a kernel function.
    Common kernel functions include Gaussian, Epanechnikov, and Triangular kernels, which determine the weight of each data point based on its distance from the point being evaluated.
    Kernel smoothing can provide a smooth estimate of the surface while preserving local features in the data.
    */
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
