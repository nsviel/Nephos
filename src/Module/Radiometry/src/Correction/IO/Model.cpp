#include "Model.h"

#include <python/matplotlibcpp.h>
#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>


namespace rad::correction::io{

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
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  model->serial_number = utl::json::read_value<string>(model->path, "serial_number");
  model->degree_x = utl::json::read_value<int>(model->path, "x.degree");
  model->axis_x.bound[0] = utl::json::read_value<float>(model->path, "x.bound_min");
  model->axis_x.bound[1] = utl::json::read_value<float>(model->path, "x.bound_max");
  model->degree_y = utl::json::read_value<int>(model->path, "y.degree");
  model->axis_y.bound[0] = utl::json::read_value<float>(model->path, "y.bound_min");
  model->axis_y.bound[1] = utl::json::read_value<float>(model->path, "y.bound_max");

  //---------------------------
}
void Model::export_model(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  utl::json::write_value(model->path, "serial_number", model->serial_number);
  utl::json::write_value(model->path, "x.degree", model->degree_x);
  utl::json::write_value(model->path, "x.bound_min", model->axis_x.bound[0]);
  utl::json::write_value(model->path, "x.bound_max", model->axis_x.bound[1]);
  utl::json::write_value(model->path, "y.degree", model->degree_y);
  utl::json::write_value(model->path, "y.bound_min", model->axis_y.bound[0]);
  utl::json::write_value(model->path, "y.bound_max", model->axis_y.bound[1]);

  vector<float> vec_coef = ope_surface->get_coefficient();
  for(int i=0; i<vec_coef.size(); i++){
    utl::json::write_value(model->path, "coefficient." + to_string(i), vec_coef[i]);
  }

  //---------------------------
}
void Model::compute_model(){
  //---------------------------

  this->build_model();
  this->compute_model_rmse();

  //---------------------------
}

}
