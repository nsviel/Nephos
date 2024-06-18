#include "Model.h"

#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>


namespace rad::correction::io{

//Constructor / Destructor
Model::Model(rad::correction::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  model->serial_number = utl::json::read_value<string>(model->path, "info.serial_number");
  model->depth_mode = utl::json::read_value<string>(model->path, "info.depth_mode");
  model->rmse = utl::json::read_value<float>(model->path, "info.rmse");

  model->degree_x = utl::json::read_value<int>(model->path, "x.degree");
  model->axis_x.bound[0] = utl::json::read_value<float>(model->path, "x.min");
  model->axis_x.bound[1] = utl::json::read_value<float>(model->path, "x.max");

  model->degree_y = utl::json::read_value<int>(model->path, "y.degree");
  model->axis_y.bound[0] = utl::json::read_value<float>(model->path, "y.min");
  model->axis_y.bound[1] = utl::json::read_value<float>(model->path, "y.max");

  model->coefficient.clear();
  int nb_coefficient = utl::json::read_value<int>(model->path, "info.nb_coefficient");
  for(int i=0; i<nb_coefficient; i++){
    float coef = utl::json::read_value<float>(model->path, "coefficient." +  to_string(i));
    model->coefficient.push_back(coef);
  }

  //---------------------------
  rad_model->update_model();
}
void Model::export_model(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  utl::json::write_value(model->path, "info.serial_number", model->serial_number);
  utl::json::write_value(model->path, "info.depth_mode", model->depth_mode);
  utl::json::write_value(model->path, "info.rmse", model->rmse);
  utl::json::write_value(model->path, "info.nb_coefficient", model->coefficient.size());

  utl::json::write_value(model->path, "x.variable", "Range");
  utl::json::write_value(model->path, "x.degree", model->degree_x);
  utl::json::write_value(model->path, "x.min", model->axis_x.bound[0]);
  utl::json::write_value(model->path, "x.max", model->axis_x.bound[1]);

  utl::json::write_value(model->path, "y.variable", "Incidence angle");
  utl::json::write_value(model->path, "y.degree", model->degree_y);
  utl::json::write_value(model->path, "y.min", model->axis_y.bound[0]);
  utl::json::write_value(model->path, "y.max", model->axis_y.bound[1]);

  for(int i=0; i<model->coefficient.size(); i++){
    utl::json::write_value(model->path, "coefficient." + to_string(i), model->coefficient[i]);
  }

  //---------------------------
}


}
