#include "Model.h"

#include <Radiometry/Correction/Namespace.h>
#include <Data/Namespace.h>
#include <Processing/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor::io{

//Constructor / Destructor
Model::Model(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();
  this->rad_io_measure = node_correction->get_rad_io_measure();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::import_model(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  std::string path = sensor->calibration.path.build();
  this->read_device_info(sensor, path);
  this->read_depth_mode_model(sensor, path);
  rad_model->update_model(sensor);
  rad_io_measure->import_measure(sensor);

  //---------------------------
}
void Model::export_model(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  std::string path = sensor->calibration.path.build();
  this->write_device_info(sensor, path);
  this->write_depth_mode_model(sensor, path);

  //---------------------------
}

//Subfunction
void Model::write_device_info(std::shared_ptr<dat::base::Sensor> sensor, std::string& path){
  //---------------------------

  //Info
  utl::json::write_value(path, "info.device", sensor->info.model);
  utl::json::write_value(path, "info.serial_number", sensor->info.serial_number);

  //Depth modes
  for(int i=0; i<sensor->info.vec_depth_mode.size(); i++){
    std::string& depth_mode = sensor->info.vec_depth_mode[i];
    utl::json::write_value(path, "depth_mode" + std::to_string(i), depth_mode);
  }

  //---------------------------
}
void Model::write_depth_mode_model(std::shared_ptr<dat::base::Sensor> sensor, std::string& path){
  dat::base::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  //---------------------------

  std::string depth_mode = sensor->info.depth_mode;

  utl::json::write_value(path, depth_mode + ".model_rmse", model->rmse);
  utl::json::write_value(path, depth_mode + ".name_measure", rad_struct->measure.path.build());
  utl::json::write_value(path, depth_mode + ".nb_coefficient", model->coefficient.size());

  //X variable
  utl::json::write_value(path, depth_mode + ".x.variable", "Range");
  utl::json::write_value(path, depth_mode + ".x.degree", model->degree_x);
  utl::json::write_value(path, depth_mode + ".x.min", model->axis_x.bound[0]);
  utl::json::write_value(path, depth_mode + ".x.max", model->axis_x.bound[1]);

  //Y variable
  utl::json::write_value(path, depth_mode + ".y.variable", "Incidence angle");
  utl::json::write_value(path, depth_mode + ".y.degree", model->degree_y);
  utl::json::write_value(path, depth_mode + ".y.min", model->axis_y.bound[0]);
  utl::json::write_value(path, depth_mode + ".y.max", model->axis_y.bound[1]);

  //Coefficient
  for(int i=0; i<model->coefficient.size(); i++){
    float& coef = model->coefficient[i];
    utl::json::write_value(path, depth_mode + ".coefficient." + std::to_string(i), coef);
  }

  //---------------------------
}
void Model::read_device_info(std::shared_ptr<dat::base::Sensor> sensor, std::string& path){
  //---------------------------

  //Info
  //sensor->info.serial_number = utl::json::read_value<std::string>(path, "info.serial_number");

  //Depth modes
  for(int i=0; i<sensor->info.vec_depth_mode.size(); i++){
    std::string& depth_mode = sensor->info.vec_depth_mode[i];
    utl::json::write_value(path, "depth_mode" + std::to_string(i), depth_mode);
  }

  //---------------------------
}
void Model::read_depth_mode_model(std::shared_ptr<dat::base::Sensor> sensor, std::string& path){
  dat::base::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  //---------------------------

  std::string depth_mode = "NFOV";

  model->rmse = utl::json::read_value<float>(path, depth_mode + ".model_rmse");
  std::string path_measure = utl::json::read_value<std::string>(path, depth_mode + ".name_measure");
  rad_struct->measure.path.insert(path_measure);

  //X variable
  model->degree_x = utl::json::read_value<int>(path, depth_mode + ".x.degree");
  model->axis_x.bound[0] = utl::json::read_value<float>(path, depth_mode + ".x.min");
  model->axis_x.bound[1] = utl::json::read_value<float>(path, depth_mode + ".x.max");

  //Y variable
  model->degree_y = utl::json::read_value<int>(path, depth_mode + ".y.degree");
  model->axis_y.bound[0] = utl::json::read_value<float>(path, depth_mode + ".y.min");
  model->axis_y.bound[1] = utl::json::read_value<float>(path, depth_mode + ".y.max");

  //Coefficient
  model->coefficient.clear();
  int nb_coefficient = utl::json::read_value<int>(path, depth_mode + ".nb_coefficient");
  for(int i=0; i<nb_coefficient; i++){
    float coef = utl::json::read_value<float>(path, depth_mode + ".coefficient." + std::to_string(i));
    model->coefficient.push_back(coef);
  }

  //---------------------------
}

}
