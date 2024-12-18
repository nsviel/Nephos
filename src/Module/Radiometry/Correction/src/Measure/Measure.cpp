#include "Measure.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor{

//Constructor / Destructor
Measure::Measure(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_plot = node_correction->get_rad_plot();

  //---------------------------
}
Measure::~Measure(){}

//Main function
void Measure::init(){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  //---------------------------

  measure.path.insert("../media/calibration/kinect_NFOV.data");

  //R
  measure.R_resolution = 0.01f;
  measure.R_range = glm::vec2(0.0f, 5.0f);
  measure.R_size = (measure.R_range.y - measure.R_range.x) / measure.R_resolution + 1;

  //It
  measure.It_resolution = 1.0f;
  measure.It_range = glm::vec2(0.0f, 90.0f);
  measure.It_size = (measure.It_range.y - measure.It_range.x) / measure.It_resolution + 1;

  //I
  measure.I_range = glm::vec2(0.0f, 1500.0f);

  //Measure
  measure.size = measure.R_size * measure.It_size;
  measure.data = std::vector<glm::vec3>(measure.size, glm::vec3(-1, -1, -1));

  //---------------------------
}

//Subfunction
void Measure::process_measure(dat::base::Sensor& sensor){
  //---------------------------

  std::vector<glm::vec3>& search_xyz = rad_struct->ransac.search_xyz;
  std::vector<float>& search_Is = rad_struct->ransac.search_Is;
  rad_struct->state.data = rad::cor::HAS_DATA;

  this->data_measure(sensor, search_xyz, search_Is);
  this->data_IfR(sensor, search_xyz, search_Is);
  this->data_IfIt(search_xyz, search_Is);

  //---------------------------
}
void Measure::data_measure(dat::base::Sensor& sensor, std::vector<glm::vec3>& search_xyz, std::vector<float>& search_Is){
  rad::cor::structure::Model* model = &rad_struct->model;
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  //Init parameter
  glm::vec3 root = glm::vec3(0, 0, 0);
  glm::vec3 pose = rad_struct->ransac.current_pose;
  float radius = rad_struct->ransac.sphere_diameter / 2;
  float thres_sphere = rad_struct->ransac.thres_sphere;

  //Insert measure
  for(int i=0; i<search_xyz.size(); i++){
    glm::vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, pose) - radius - 0.04;

    if(distance <= thres_sphere){
      glm::vec3 Nxyz = glm::normalize(xyz - pose);
      float Is = search_Is[i];
      float R = math::distance_from_origin(xyz);
      float It = math::compute_It(xyz, Nxyz, R);

      //R limite validity
      if(R < model->axis_x.bound[0]) model->axis_x.bound[0] = R;
      if(R > model->axis_x.bound[1]) model->axis_x.bound[1] = R;

      // Calculate the index of the cell in the heatmap grid
      int i = static_cast<int>((R - plot.IfRIt.axis_x.min) / (plot.IfRIt.axis_x.max - plot.IfRIt.axis_x.min) * plot.IfRIt.axis_x.size);
      int j = static_cast<int>((It - plot.IfRIt.axis_y.max) / (plot.IfRIt.axis_y.min - plot.IfRIt.axis_y.max) * plot.IfRIt.axis_y.size);
      int index = j * plot.IfRIt.axis_x.size + i;
      if(index >= 0 && index < plot.IfRIt.axis_z.size){
        plot.IfRIt.axis_z.data[index] = Is;
        measure.data[index] = glm::vec3(R, It, Is);
      }
    }
  }

  //---------------------------
}
void Measure::data_IfR(dat::base::Sensor& sensor, std::vector<glm::vec3>& search_xyz, std::vector<float>& search_Is){
  rad::cor::structure::Model* model = &rad_struct->model;
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  //Search for closest point
  int idx = rad_struct->ransac.idx_nearest;
  float R = math::distance_from_origin(search_xyz[idx]);
  float Is = search_Is[idx];

  //Insert measure
  int index = static_cast<int>(std::round(R / plot.IfR.axis_x.resolution));
  if(index >= 0 && index < plot.IfR.axis_x.data.size()){
    plot.IfR.axis_x.data[index] = R;
    plot.IfR.axis_y.data[index] = Is;
    plot.IfR.highlight = glm::vec2(R, Is);
    model->axis_x.current = R;
  }

  //---------------------------
}
void Measure::data_IfIt(std::vector<glm::vec3>& search_xyz, std::vector<float>& search_Is){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  //Init parameter
  glm::vec3 root = glm::vec3(0, 0, 0);
  glm::vec3 pose = rad_struct->ransac.current_pose;
  float radius = rad_struct->ransac.sphere_diameter / 2;
  float thres_sphere = rad_struct->ransac.thres_sphere;

  plot.IfIt.axis_x.data = std::vector<float>(plot.IfIt.axis_x.data.size(), 0.0f);
  plot.IfIt.axis_y.data = std::vector<float>(plot.IfIt.axis_y.data.size(), 0.0f);

  //Insert measure
  for(int i=0; i<search_xyz.size(); i++){
    glm::vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, pose) - radius - 0.04;

    if(distance <= thres_sphere){
      glm::vec3 Nxyz = glm::normalize(xyz - pose);
      float Is = search_Is[i];
      float R = math::distance_from_origin(xyz);
      float It = math::compute_It(xyz, Nxyz, R);

      //Add into model data vector
      int index = static_cast<int>(std::round(It / plot.IfIt.axis_x.resolution));
      plot.IfIt.axis_x.data[index] = It;
      plot.IfIt.axis_y.data[index] = Is;
    }
  }

  //---------------------------
}

}
