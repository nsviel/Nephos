#include "Model.h"

#include <Radiometry/Correction/Namespace.h>
#include <Operation/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::cor{

//Constructor / Destructor
Model::Model(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->ope_polyfit = new ope::fitting::Polyfit();
  this->ope_surface = new ope::fitting::Surface();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::compute_model(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  this->build_model(sensor);
  this->rmse_model(sensor);

  //---------------------------
}
void Model::clear_model(){
  //---------------------------



  //---------------------------
}

//Subfunction
void Model::build_model(std::shared_ptr<dat::base::Sensor> sensor){
  dat::sensor::Model* model = get_model(sensor, "NFOV");
  //---------------------------

  //Apply logarithmic scale
  std::vector<glm::vec3> vec_data = rad_struct->measure.data;
  for(int i=0; i<vec_data.size(); i++){
    glm::vec3& data = vec_data[i];
    data.z = std::log(data.z);
  }

  //Optimization algorithm
  ope_surface->set_degree(model->degree_x, model->degree_y);
  ope_surface->compute(vec_data, model->axis_x.bound, model->axis_y.bound);
  model->coefficient = ope_surface->get_coefficient();

  //---------------------------
}
void Model::update_model(std::shared_ptr<dat::base::Sensor> sensor){
  dat::sensor::Model* model = get_model(sensor, "NFOV");
  //---------------------------

  ope_surface->set_degree(model->degree_x, model->degree_y);
  ope_surface->set_coefficients(model->coefficient);

  //---------------------------
}
void Model::find_model_bound(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  glm::vec2 R_bound = glm::vec2(1000, 0);
  glm::vec2 It_bound = glm::vec2(1000, 0);

  for(int i=0; i<rad_struct->measure.data.size(); i++){
    //R
    float& R = rad_struct->measure.data[i].x;
    if(R < 0) continue;
    if(R < R_bound.x) R_bound.x = R;
    if(R > R_bound.y) R_bound.y = R;

    //It
    float& It = rad_struct->measure.data[i].y;
    if(It < 0) continue;
    if(It < It_bound.x) It_bound.x = It;
    if(It > It_bound.y) It_bound.y = It;
  }

  rad_struct->model.axis_x.bound = R_bound;
  rad_struct->model.axis_y.bound = It_bound;
  rad_struct->model.axis_x.current = (R_bound.x + R_bound.y) / 2;
  rad_struct->model.axis_y.current = (It_bound.x + It_bound.y) / 2;

  //---------------------------
}
float Model::rmse_model(std::shared_ptr<dat::base::Sensor> sensor){
  dat::sensor::Model* model = get_model(sensor, "NFOV");
  if(!is_model_build(sensor)) return 0;
  //---------------------------

  int N = rad_struct->measure.data.size();
  float E = 0;
  for(int i=0; i<N; i++){
    glm::vec3& data = rad_struct->measure.data[i];
    if(data.x < model->axis_x.bound[0] || data.x > model->axis_x.bound[1]) continue;
    if(data.y < model->axis_y.bound[0] || data.y > model->axis_y.bound[1]) continue;
    if(data.x < 0 || data.y < 0) continue;

    float z = apply_model(data.x, data.y);
    E += pow(z - data.z, 2);
  }

  float RMSE = sqrt(E / N);
  model->rmse = RMSE;

  //---------------------------
  return RMSE;
}
float Model::apply_model(float x, float y){
  //---------------------------

  /*
  //Function and coef from python code
  std::vector<float> vec_coef;
  vec_coef.push_back(8.74097349);
  vec_coef.push_back(-1.42552352);
  vec_coef.push_back(-0.0182150385);
  vec_coef.push_back(0.100452890);
  vec_coef.push_back(-0.000202683733);
  vec_coef.push_back(0.00501210320);
  //float z = vec_coef[0] + vec_coef[1] * x + vec_coef[2] * y + vec_coef[3] * pow(x, 2) + vec_coef[4] * pow(y, 2) + vec_coef[5] * x * y;
  */

  float z = ope_surface->evaluate(x, y);

  //Reconvert from log scale to normal scale
  z = std::exp(z);
  if(z < 0) z = 0;

  //---------------------------
  return z;
}

//Checker function
dat::sensor::Model* Model::get_model(std::shared_ptr<dat::base::Sensor> sensor, std::string depth_mode){
  //---------------------------

  //Search for model
  for(int i=0; i<sensor->calibration.vec_model.size(); i++){
    dat::sensor::Model* model = &sensor->calibration.vec_model[i];
    if(model->depth_mode == depth_mode){
      return model;
    }
  }

  //Else create it
  dat::sensor::Model model;
  model.depth_mode = depth_mode;
  sensor->calibration.vec_model.push_back(model);

  //---------------------------
  return get_model(sensor, depth_mode);
}
bool Model::is_model_build(std::shared_ptr<dat::base::Sensor> sensor){
  if(is_model_loaded(sensor) == false) return false;
  //---------------------------

  dat::sensor::Model* model = get_model(sensor, "NFOV");
  if(model->coefficient.size() == 0){
    return false;
  }else{
    return true;
  }

  //---------------------------
}
bool Model::is_model_loaded(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  if(sensor->calibration.vec_model.size() != 0){
    return true;
  }else{
    return false;
  }

  //---------------------------
}

}
