#include "Model.h"

#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Model::Model(rad::correction::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_plot = new rad::correction::Plot(node_correction);
  this->rad_measure = new rad::correction::Measure(node_correction);
  this->ope_polyfit = new ope::fitting::Polyfit();
  this->ope_surface = new ope::fitting::Surface();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
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
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
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
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
  //---------------------------

  //Apply logarithmic scale
  std::vector<glm::vec3> vec_data = rad_struct->measure.data;
  for(int i=0; i<vec_data.size(); i++){
    glm::vec3& data = vec_data[i];
    data.z = std::log(data.z);
  }

  //Optimization algorithm
  ope_surface->set_degree(optim->degree_x, optim->degree_y);
  ope_surface->compute(vec_data, optim->axis_x.bound, optim->axis_y.bound);
  optim->coefficient = ope_surface->get_coefficient();

  //---------------------------
}
float Model::compute_model_rmse(){
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
  //---------------------------

  int N = rad_struct->measure.data.size();
  float E = 0;
  for(int i=0; i<N; i++){
    vec3& data = rad_struct->measure.data[i];
    if(data.x < optim->axis_x.bound[0] || data.x > optim->axis_x.bound[1]) continue;
    if(data.y < optim->axis_y.bound[0] || data.y > optim->axis_y.bound[1]) continue;
    if(data.x < 0 || data.y < 0) continue;

    float z = apply_model(data.x, data.y);
    E += pow(z - std::log(data.z), 2);
  }

  float RMSE = sqrt(E / N);
  optim->rmse = RMSE;

  //---------------------------
  return RMSE;
}
float Model::apply_model(float x, float y){
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
  if(optim->coefficient.size() == 0) return 0;
  //---------------------------
say(optim->coefficient.size());
  //Function and coef from python code
  vector<float> vec_coef;
  vec_coef.push_back(8.74097349);
  vec_coef.push_back(-1.42552352);
  vec_coef.push_back(-0.0182150385);
  vec_coef.push_back(0.100452890);
  vec_coef.push_back(-0.000202683733);
  vec_coef.push_back(0.00501210320);
  //float z = vec_coef[0] + vec_coef[1] * x + vec_coef[2] * y + vec_coef[3] * pow(x, 2) + vec_coef[4] * pow(y, 2) + vec_coef[5] * x * y;

  float z = ope_surface->evaluate(x, y);
  z = std::exp(z);

  if(z < 0) z = 0;

  //---------------------------
  return z;
}
bool Model::is_ready(){
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
  //---------------------------

  if(optim->coefficient.size() == 0){
    return false;
  }else{
    return true;
  }

  //---------------------------
}

}
