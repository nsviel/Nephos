#include "Model.h"

#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>

namespace rad::model{

//Constructor / Destructor
Model::Model(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->ope_polyfit = new ope::fitting::Polyfit();
  this->ope_surface = new ope::fitting::Surface();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  //---------------------------

  optim->serial_number = utl::json::read_value<string>(optim->path, "serial_number");
  optim->degree_x = utl::json::read_value<int>(optim->path, "x.degree");
  optim->axis_x.bound[0] = utl::json::read_value<float>(optim->path, "x.bound_min");
  optim->axis_x.bound[1] = utl::json::read_value<float>(optim->path, "x.bound_max");
  optim->degree_y = utl::json::read_value<int>(optim->path, "y.degree");
  optim->axis_y.bound[0] = utl::json::read_value<float>(optim->path, "y.bound_min");
  optim->axis_y.bound[1] = utl::json::read_value<float>(optim->path, "y.bound_max");

  //---------------------------
}
void Model::export_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  //---------------------------

  utl::json::write_value(optim->path, "serial_number", optim->serial_number);
  utl::json::write_value(optim->path, "x.degree", optim->degree_x);
  utl::json::write_value(optim->path, "x.bound_min", optim->axis_x.bound[0]);
  utl::json::write_value(optim->path, "x.bound_max", optim->axis_x.bound[1]);
  utl::json::write_value(optim->path, "y.degree", optim->degree_y);
  utl::json::write_value(optim->path, "y.bound_min", optim->axis_y.bound[0]);
  utl::json::write_value(optim->path, "y.bound_max", optim->axis_y.bound[1]);

  vector<float> vec_coef = ope_surface->get_coefficient();
  for(int i=0; i<vec_coef.size(); i++){
    utl::json::write_value(optim->path, "coefficient." + to_string(i), vec_coef[i]);
  }

  //---------------------------
}
void Model::compute_model(){
  //---------------------------

  this->build_model();
  this->compute_model_rmse();

  //---------------------------
}

//Subfunction
void Model::build_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Apply logarithmic scale
  std::vector<glm::vec3> vec_data = measure->data;
  for(int i=0; i<vec_data.size(); i++){
    glm::vec3& data = vec_data[i];
    data.z = log(data.z);
  }

  //Optimization algorithm
  ope_surface->set_degree(optim->degree_x, optim->degree_y);
  ope_surface->compute(vec_data, optim->axis_x.bound, optim->axis_y.bound);
  rad_struct->model.optim.coefficient = ope_surface->get_coefficient();

  //---------------------------
}
float Model::compute_model_rmse(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  int N = measure->data.size();
  float E = 0;
  for(int i=0; i<N; i++){
    vec3& data = measure->data[i];
    if(data.x < optim->axis_x.bound[0] || data.x > optim->axis_x.bound[1]) continue;
    if(data.y < optim->axis_y.bound[0] || data.y > optim->axis_y.bound[1]) continue;
    if(data.x < 0 || data.y < 0) continue;

    float z = apply_model(data.x, data.y);
    E += pow(z - log(data.z), 2);
  }

  float RMSE = sqrt(E / N);
  optim->rmse = RMSE;

  //---------------------------
  return RMSE;
}
float Model::apply_model(float x, float y){
  if(rad_struct->model.optim.coefficient.size() == 0) return 0;
  //---------------------------

  float z = ope_surface->evaluate(x, y);

  if(z < 0) z = 0;

  //---------------------------
  return z;
}

}
