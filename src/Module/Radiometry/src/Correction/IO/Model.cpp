#include "Model.h"

#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>


namespace rad::correction::io{

//Constructor / Destructor
Model::Model(rad::correction::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();
  this->rad_io_measure = node_correction->get_rad_io_measure();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(){
  //---------------------------

  this->write_device_info();
  this->write_depth_mode_model();
  rad_model->update_model();

  //---------------------------
}
void Model::export_model(){
  //---------------------------

  this->write_device_info();
  this->write_depth_mode_model();

  //---------------------------
}

//Subfunction
void Model::write_device_info(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  string path = get_current_path();

  //Info
  utl::json::write_value(path, "info.device", model->device);
  utl::json::write_value(path, "info.serial_number", model->serial_number);

  //Depth modes
  for(int i=0; i<model->mode.size(); i++){
    std::string& depth_mode = model->mode[i];
    utl::json::write_value(path, "depth_mode" + to_string(i), depth_mode);
  }

  //---------------------------
}
void Model::write_depth_mode_model(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  string path = get_current_path();

  utl::json::write_value(path, model->depth_mode + ".model_rmse", model->rmse);
  utl::json::write_value(path, model->depth_mode + ".name_measure", model->name_measure);
  utl::json::write_value(path, model->depth_mode + ".nb_coefficient", model->coefficient.size());

  utl::json::write_value(path, model->depth_mode + ".x.variable", "Range");
  utl::json::write_value(path, model->depth_mode + ".x.degree", model->degree_x);
  utl::json::write_value(path, model->depth_mode + ".x.min", model->axis_x.bound[0]);
  utl::json::write_value(path, model->depth_mode + ".x.max", model->axis_x.bound[1]);

  utl::json::write_value(path, model->depth_mode + ".y.variable", "Incidence angle");
  utl::json::write_value(path, model->depth_mode + ".y.degree", model->degree_y);
  utl::json::write_value(path, model->depth_mode + ".y.min", model->axis_y.bound[0]);
  utl::json::write_value(path, model->depth_mode + ".y.max", model->axis_y.bound[1]);

  for(int i=0; i<model->coefficient.size(); i++){
    float& coef = model->coefficient[i];
    utl::json::write_value(path, model->depth_mode + ".coefficient." + to_string(i), coef);
  }

  //---------------------------
}
void Model::read_device_info(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------

  string path = get_current_path();

  //Info
  model->serial_number = utl::json::read_value<string>(path, "info.serial_number");

  //Depth modes
  for(int i=0; i<model->mode.size(); i++){
    std::string& depth_mode = model->mode[i];
    utl::json::write_value(path, "depth_mode" + to_string(i), depth_mode);
  }

  //---------------------------
}
void Model::read_depth_mode_model(){
  rad::correction::structure::Model* model = &rad_struct->model;
  //---------------------------
  string path = get_current_path();

  model->depth_mode = utl::json::read_value<string>(path, "info.depth_mode");

  model->rmse = utl::json::read_value<float>(path, "info.model_rmse");
  model->name_measure = utl::json::read_value<float>(path, "info.name_measure");

  model->degree_x = utl::json::read_value<int>(path, "x.degree");
  model->axis_x.bound[0] = utl::json::read_value<float>(path, "x.min");
  model->axis_x.bound[1] = utl::json::read_value<float>(path, "x.max");

  model->degree_y = utl::json::read_value<int>(path, "y.degree");
  model->axis_y.bound[0] = utl::json::read_value<float>(path, "y.min");
  model->axis_y.bound[1] = utl::json::read_value<float>(path, "y.max");

  model->coefficient.clear();
  int nb_coefficient = utl::json::read_value<int>(path, "info.nb_coefficient");
  for(int i=0; i<nb_coefficient; i++){
    float coef = utl::json::read_value<float>(path, "coefficient." +  to_string(i));
    model->coefficient.push_back(coef);
  }

  //---------------------------
}
std::string Model::get_current_path(){
  //---------------------------

  std::string& dir = rad_struct->model.path_dir;
  std::string& filename = rad_struct->model.name_model;
  std::string path = dir + "/" + filename;

  //---------------------------
  return path;
}

}
