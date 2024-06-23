#include "Model.h"

#include <Utility/Function/File/Json.cpp>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


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
void Model::import_model(dyn::base::Sensor* sensor){
  string path = sensor->correction.path.build();
  //---------------------------

  this->read_device_info(sensor, path);
  this->read_depth_mode_model(sensor, path);
  rad_model->update_model(sensor);
  rad_io_measure->import_measure(sensor);

  //---------------------------
}
void Model::export_model(dyn::base::Sensor* sensor){
  string path = sensor->correction.path.build();
  //---------------------------

  this->write_device_info(sensor, path);
  this->write_depth_mode_model(sensor, path);

  //---------------------------
}

//Subfunction
void Model::write_device_info(dyn::base::Sensor* sensor, string& path){
  //---------------------------

  //Info
  utl::json::write_value(path, "info.device", sensor->device_name);
  utl::json::write_value(path, "info.serial_number", sensor->serial_number);

  //Depth modes
  for(int i=0; i<sensor->vec_depth_mode.size(); i++){
    std::string& depth_mode = sensor->vec_depth_mode[i];
    utl::json::write_value(path, "depth_mode" + to_string(i), depth_mode);
  }

  //---------------------------
}
void Model::write_depth_mode_model(dyn::base::Sensor* sensor, string& path){
  //---------------------------

  std::string depth_mode = sensor->depth_mode;

  utl::json::write_value(path, depth_mode + ".model_rmse", sensor->correction.rmse);
  utl::json::write_value(path, depth_mode + ".name_measure", rad_struct->measure.path.build());
  utl::json::write_value(path, depth_mode + ".nb_coefficient", sensor->correction.coefficient.size());

  //X variable
  utl::json::write_value(path, depth_mode + ".x.variable", "Range");
  utl::json::write_value(path, depth_mode + ".x.degree", sensor->correction.degree_x);
  utl::json::write_value(path, depth_mode + ".x.min", sensor->correction.axis_x.bound[0]);
  utl::json::write_value(path, depth_mode + ".x.max", sensor->correction.axis_x.bound[1]);

  //Y variable
  utl::json::write_value(path, depth_mode + ".y.variable", "Incidence angle");
  utl::json::write_value(path, depth_mode + ".y.degree", sensor->correction.degree_y);
  utl::json::write_value(path, depth_mode + ".y.min", sensor->correction.axis_y.bound[0]);
  utl::json::write_value(path, depth_mode + ".y.max", sensor->correction.axis_y.bound[1]);

  //Coefficient
  for(int i=0; i<sensor->correction.coefficient.size(); i++){
    float& coef = sensor->correction.coefficient[i];
    utl::json::write_value(path, depth_mode + ".coefficient." + to_string(i), coef);
  }

  //---------------------------
}
void Model::read_device_info(dyn::base::Sensor* sensor, string& path){
  //---------------------------

  //Info
  //sensor->serial_number = utl::json::read_value<string>(path, "info.serial_number");

  //Depth modes
  for(int i=0; i<sensor->vec_depth_mode.size(); i++){
    std::string& depth_mode = sensor->vec_depth_mode[i];
    utl::json::write_value(path, "depth_mode" + to_string(i), depth_mode);
  }

  //---------------------------
}
void Model::read_depth_mode_model(dyn::base::Sensor* sensor, string& path){
  //---------------------------

  std::string depth_mode = "NFOV";

  sensor->correction.rmse = utl::json::read_value<float>(path, depth_mode + ".model_rmse");
  std::string path_measure = utl::json::read_value<string>(path, depth_mode + ".name_measure");
  rad_struct->measure.path.insert(path_measure);

  //X variable
  sensor->correction.degree_x = utl::json::read_value<int>(path, depth_mode + ".x.degree");
  sensor->correction.axis_x.bound[0] = utl::json::read_value<float>(path, depth_mode + ".x.min");
  sensor->correction.axis_x.bound[1] = utl::json::read_value<float>(path, depth_mode + ".x.max");

  //Y variable
  sensor->correction.degree_y = utl::json::read_value<int>(path, depth_mode + ".y.degree");
  sensor->correction.axis_y.bound[0] = utl::json::read_value<float>(path, depth_mode + ".y.min");
  sensor->correction.axis_y.bound[1] = utl::json::read_value<float>(path, depth_mode + ".y.max");

  //Coefficient
  sensor->correction.coefficient.clear();
  int nb_coefficient = utl::json::read_value<int>(path, depth_mode + ".nb_coefficient");
  for(int i=0; i<nb_coefficient; i++){
    float coef = utl::json::read_value<float>(path, depth_mode + ".coefficient." +  to_string(i));
    sensor->correction.coefficient.push_back(coef);
  }

  //---------------------------
}

}
