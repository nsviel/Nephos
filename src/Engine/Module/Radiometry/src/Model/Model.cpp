#include "Model.h"

#include <K4N/Namespace.h>
#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>

namespace radio{

//Constructor / Destructor
Model::Model(radio::Structure* radio_struct){
  //---------------------------

  this->radio_struct = radio_struct;
  this->ope_polyfit = new ope::fitting::Polyfit();
  this->ope_surface = new ope::fitting::Surface();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  radio::structure::Optimization* model = &radio_struct->model.optim;
  //---------------------------

  model->serial_number = utl::json::read_value<string>(model->path, "serial_number");
  model->degree_x = utl::json::read_value<int>(model->path, "x.degree");
  model->x.bound[0] = utl::json::read_value<float>(model->path, "x.bound_min");
  model->x.bound[1] = utl::json::read_value<float>(model->path, "x.bound_max");
  model->degree_y = utl::json::read_value<int>(model->path, "y.degree");
  model->y.bound[0] = utl::json::read_value<float>(model->path, "y.bound_min");
  model->y.bound[1] = utl::json::read_value<float>(model->path, "y.bound_max");

  //---------------------------
}
void Model::export_model(){
  radio::structure::Optimization* model = &radio_struct->model.optim;
  //---------------------------

  utl::json::write_value(model->path, "serial_number", model->serial_number);
  utl::json::write_value(model->path, "x.degree", model->degree_x);
  utl::json::write_value(model->path, "x.bound_min", model->x.bound[0]);
  utl::json::write_value(model->path, "x.bound_max", model->x.bound[1]);
  utl::json::write_value(model->path, "y.degree", model->degree_y);
  utl::json::write_value(model->path, "y.bound_min", model->y.bound[0]);
  utl::json::write_value(model->path, "y.bound_max", model->y.bound[1]);

  vector<float> vec_coef = ope_surface->get_coefficient();
  for(int i=0; i<vec_coef.size(); i++){
    utl::json::write_value(model->path, "coefficient." + to_string(i), vec_coef[i]);
  }

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
  radio::structure::Optimization* model = &radio_struct->model.optim;
  //---------------------------

  //if(ope_surface->has_been_computed() == false){
    this->compute_model();
  //}

  // Generate values for x and y
  std::vector<float> x_values;
  for(float i = model->x.bound[0]; i <= model->x.bound[1]; i += 0.1){
    x_values.push_back(i);
  }

  std::vector<float> y_values;
  for(float i = model->y.bound[0]; i <= model->y.bound[1]; i += 1.0){
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
void Model::make_model(){
  radio::structure::Optimization* model = &radio_struct->model.optim;
  radio::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  ope_surface->compute(measure->vec_data, model->x.bound, model->y.bound);

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
  radio::structure::Optimization* model = &radio_struct->model.optim;
  radio::structure::Measure* measure = &radio_struct->model.measure;
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
