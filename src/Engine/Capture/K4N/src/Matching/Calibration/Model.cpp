#include "Model.h"

#include <K4N/Namespace.h>
#include <python/matplotlibcpp.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->ope_polyfit = new ope::fitting::Polyfit();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------


  //---------------------------
}
void Model::export_model(){
  //---------------------------


  //---------------------------
}
void Model::compute_model(){
  //---------------------------

  this->make_model();
  this->validation_model();

  //---------------------------
}


//Subfunction
void Model::draw_model(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  if(ope_polyfit->has_been_computed() == false){
    this->compute_model();
  }

  std::vector<std::vector<double>> x, y, z;

  // Generate values for x and y
  std::vector<double> x_values;
  for(double i = model->x.bound[0]; i <= model->x.bound[1]; i += 0.1){
    x_values.push_back(i);
  }

  std::vector<double> y_values;
  for(double i = model->y.bound[0]; i <= model->y.bound[1]; i += 1.0){
    y_values.push_back(i);
  }

  // Compute z values and fill x, y, and z vectors
  for (double x_val : x_values) {
    std::vector<double> row_x, row_y, row_z;
    for (double y_val : y_values) {
      row_x.push_back(x_val);
      row_y.push_back(y_val);
      row_z.push_back(this->apply_model(x_val, y_val));
    }
    x.push_back(row_x);
    y.push_back(row_y);
    z.push_back(row_z);
  }

  matplotlibcpp::plot_surface(x, y, z);
  matplotlibcpp::show();

  //---------------------------
}
void Model::make_model(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  k4n::structure::Measure* measure = &k4n_struct->matching.measure;
  //---------------------------

  ope_polyfit->compute(measure->vec_data, model->degree, model->x.bound, model->y.bound);


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
  k4n::structure::Model* model = &k4n_struct->matching.model;
  k4n::structure::Measure* measure = &k4n_struct->matching.measure;
  //---------------------------

  int N = measure->vec_data.size();
  float E = 0;
  for(int i=0; i<N; i++){
    vec3& data = measure->vec_data[i];
    if(data.x < model->x.bound[0] || data.x > model->x.bound[1]) continue;
    if(data.y < model->y.bound[0] || data.y > model->y.bound[1]) continue;
    float z = apply_model(data.x, data.y);
    E += pow(z - data.z, 2);
  }

  float RMSE = sqrt(E / N);
  model->rmse = RMSE;

  //---------------------------
  return RMSE;
}

}
