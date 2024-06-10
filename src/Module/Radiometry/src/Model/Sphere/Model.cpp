#include "Model.h"

#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>


namespace rad::model::sphere{

//Constructor / Destructor
Model::Model(rad::model::Node* node_model){
  //---------------------------

  this->rad_struct = node_model->get_rad_struct();
  this->ope_polyfit = new ope::fitting::Polyfit();
  this->ope_surface = new ope::fitting::Surface();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  rad::model::structure::Optimization* optim = &rad_struct->optim;
  //---------------------------

  rad_struct->optim.serial_number = utl::json::read_value<string>(rad_struct->optim.path, "serial_number");
  rad_struct->optim.degree_x = utl::json::read_value<int>(rad_struct->optim.path, "x.degree");
  rad_struct->optim.axis_x.bound[0] = utl::json::read_value<float>(rad_struct->optim.path, "x.bound_min");
  rad_struct->optim.axis_x.bound[1] = utl::json::read_value<float>(rad_struct->optim.path, "x.bound_max");
  rad_struct->optim.degree_y = utl::json::read_value<int>(rad_struct->optim.path, "y.degree");
  rad_struct->optim.axis_y.bound[0] = utl::json::read_value<float>(rad_struct->optim.path, "y.bound_min");
  rad_struct->optim.axis_y.bound[1] = utl::json::read_value<float>(rad_struct->optim.path, "y.bound_max");

  //---------------------------
}
void Model::export_model(){
  rad::model::structure::Optimization* optim = &rad_struct->optim;
  //---------------------------

  utl::json::write_value(rad_struct->optim.path, "serial_number", rad_struct->optim.serial_number);
  utl::json::write_value(rad_struct->optim.path, "x.degree", rad_struct->optim.degree_x);
  utl::json::write_value(rad_struct->optim.path, "x.bound_min", rad_struct->optim.axis_x.bound[0]);
  utl::json::write_value(rad_struct->optim.path, "x.bound_max", rad_struct->optim.axis_x.bound[1]);
  utl::json::write_value(rad_struct->optim.path, "y.degree", rad_struct->optim.degree_y);
  utl::json::write_value(rad_struct->optim.path, "y.bound_min", rad_struct->optim.axis_y.bound[0]);
  utl::json::write_value(rad_struct->optim.path, "y.bound_max", rad_struct->optim.axis_y.bound[1]);

  vector<float> vec_coef = ope_surface->get_coefficient();
  for(int i=0; i<vec_coef.size(); i++){
    utl::json::write_value(rad_struct->optim.path, "coefficient." + to_string(i), vec_coef[i]);
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
  //---------------------------

  //Apply logarithmic scale
  std::vector<glm::vec3> vec_data = rad_struct->sphere.data;
  for(int i=0; i<vec_data.size(); i++){
    glm::vec3& data = vec_data[i];
    data.z = std::log(data.z);
  }

  //Optimization algorithm
  ope_surface->set_degree(rad_struct->optim.degree_x, rad_struct->optim.degree_y);
  ope_surface->compute(vec_data, rad_struct->optim.axis_x.bound, rad_struct->optim.axis_y.bound);
  rad_struct->optim.coefficient = ope_surface->get_coefficient();

  //---------------------------
}
float Model::compute_model_rmse(){
  //---------------------------

  int N = rad_struct->sphere.data.size();
  float E = 0;
  for(int i=0; i<N; i++){
    vec3& data = rad_struct->sphere.data[i];
    if(data.x < rad_struct->optim.axis_x.bound[0] || data.x > rad_struct->optim.axis_x.bound[1]) continue;
    if(data.y < rad_struct->optim.axis_y.bound[0] || data.y > rad_struct->optim.axis_y.bound[1]) continue;
    if(data.x < 0 || data.y < 0) continue;

    float z = apply_model(data.x, data.y);
    E += pow(z - std::log(data.z), 2);
  }

  float RMSE = sqrt(E / N);
  rad_struct->optim.rmse = RMSE;

  //---------------------------
  return RMSE;
}
float Model::apply_model(float x, float y){
  //if(rad_struct->optim.coefficient.size() == 0) return 0;
  //---------------------------

  //Function and coef from python code
  vector<float> vec_coef;
  vec_coef.push_back(9.93334164);
  vec_coef.push_back(-2.23728476);
  vec_coef.push_back(-0.00918389259);
  vec_coef.push_back(0.254502204);
  vec_coef.push_back(-0.000355159491);
  vec_coef.push_back(0.00495704902);
  float z = vec_coef[0] + vec_coef[1] * x + vec_coef[2] * y + vec_coef[3] * pow(x, 2) + vec_coef[4] * pow(y, 2) + vec_coef[5] * x * y;

  //float z = ope_surface->evaluate(x, y);
  z = std::exp(z);

  if(z < 0) z = 0;

  //---------------------------
  return z;
}
bool Model::is_ready(){
  //---------------------------

  if(rad_struct->optim.coefficient.size() == 0){
    return false;
  }else{
    return true;
  }

  //---------------------------
}

}
