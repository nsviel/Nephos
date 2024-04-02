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
void Model::import(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------


  //---------------------------
}
void Model::export(){
  //---------------------------


  //---------------------------
}


//Subfunction
void Model::make_model(){
  //---------------------------

  vector<vec3>& vec_data = k4n_struct->matching.model.vec_data;
  vec2& x_bound = k4n_struct->matching.model.x.bound;
  vec2& y_bound = k4n_struct->matching.model.y.bound;
  int& degree = k4n_struct->matching.model.degree;
  ope_polyfit->compute(vec_data, degree, x_bound, y_bound);


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
float Model::validation_model(){
  vector<vec3>& vec_data = k4n_struct->matching.model.vec_data;
  //---------------------------

  float sum = 0;
  for(int i=0; i<vec_data.size(); i++){
    vec3& data = vec_data[i];
    if(data.x < k4n_struct->matching.model.x.bound[0] || data.x > k4n_struct->matching.model.x.bound[1]) continue;
    if(data.y < k4n_struct->matching.model.y.bound[0] || data.y > k4n_struct->matching.model.y.bound[1]) continue;
    float z = apply_model(data.x, data.y);
    sum += z - data.z;
  }

  float error = sum / vec_data.size();

  cout<<"Model mean error = "<<error<<endl;

  //---------------------------
  return error;
}

}
