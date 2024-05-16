#include "Model.h"

#include <Kinect/Namespace.h>
#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>

namespace rad{

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

  this->make_model();
  this->validation_model();
  this->update_plot_data();

  //---------------------------
}
void Model::draw_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  //---------------------------

  //if(ope_surface->has_been_computed() == false){
    this->compute_model();
  //}

  // Generate values for x and y
  std::vector<float> x_values;
  for(float i = optim->axis_x.bound[0]; i <= optim->axis_x.bound[1]; i += 0.1){
    x_values.push_back(i);
  }

  std::vector<float> y_values;
  for(float i = optim->axis_y.bound[0]; i <= optim->axis_y.bound[1]; i += 1.0){
    y_values.push_back(i);
  }

  // Compute z values and fill x, y, and z vectors
  std::vector<std::vector<float>> x, y, z;
  for(float x_val : x_values){
    std::vector<float> row_x, row_y, row_z;
    for(float y_val : y_values){
      row_x.push_back(x_val);
      row_y.push_back(y_val);

      float z_value = apply_model(x_val, y_val);
      row_z.push_back(z_value);
    }
    x.push_back(row_x);
    y.push_back(row_y);
    z.push_back(row_z);
  }

  if(z.size() == 0) return;
  matplotlibcpp::plot_surface(x, y, z);
  matplotlibcpp::show();

  //---------------------------
}

//Subfunction
void Model::make_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Apply logarithmic scale
  std::vector<glm::vec3> vec_data = measure->vec_data;
  for(int i=0; i<vec_data.size(); i++){
    glm::vec3& data = vec_data[i];
    data.z = log(data.z);
  }

  //Optimization algorithm
  ope_surface->set_degree(optim->degree_x, optim->degree_y);
  ope_surface->compute(vec_data, optim->axis_x.bound, optim->axis_y.bound);

  //---------------------------
}
float Model::apply_model(float x, float y){
  //---------------------------

  float z = ope_surface->evaluate(x, y);

  if(z < 0) z = 0;

  //---------------------------
  return z;
}
float Model::validation_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  int N = measure->vec_data.size();
  float E = 0;
  for(int i=0; i<N; i++){
    vec3& data = measure->vec_data[i];
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
void Model::update_plot_data(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  utl::type::Plot* plot = &measure->IfR;
  for(int i=0; i<plot->axis_x.data.size(); i++){
    float& x = plot->axis_x.data[i];
    float& y = plot->axis_y.data[i];
    float z = apply_model(x, y);
    //plot->axis_x.fitting.push_back();
    //plot->axis_y.fitting = z;
  }



  //---------------------------
}

}
