#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Measure::Measure(rad::detection::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  rad::model::Node* node_model = node_radio->get_node_model();

  this->model_struct = node_model->get_rad_struct();
  this->rad_struct = node_detection->get_rad_struct();

  //---------------------------
}
Measure::~Measure(){}

//Main function
void Measure::process_measure(){
  //---------------------------

  vector<vec3>& search_xyz = rad_struct->sphere.ransac.search_xyz;
  vector<float>& search_Is = rad_struct->sphere.ransac.search_Is;
  rad_struct->sphere.state_data = rad::detection::HAS_DATA;

  this->data_measure(search_xyz, search_Is);
  this->data_IfR(search_xyz, search_Is);
  this->data_IfIt(search_xyz, search_Is);

  //---------------------------
}

//Subfunction
void Measure::data_measure(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::model::sphere::structure::Optimization* optim = &model_struct->sphere.optim;
  rad::model::sphere::structure::Sphere* sphere = &model_struct->sphere.sphere;
  rad::model::sphere::structure::Plot* plot = &model_struct->sphere.plot;
  //---------------------------

  //Init parameter
  glm::vec3 root = glm::vec3(0, 0, 0);
  glm::vec3 pose = rad_struct->sphere.ransac.current_pose;
  float radius = rad_struct->sphere.ransac.sphere_diameter / 2;
  float thres_sphere = rad_struct->sphere.ransac.thres_sphere;

  //Insert measure
  for(int i=0; i<search_xyz.size(); i++){
    glm::vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, pose) - radius + 0.02;

    if(distance <= thres_sphere){
      glm::vec3 Nxyz = glm::normalize(xyz - pose);
      float Is = search_Is[i];
      float It = math::compute_It(xyz, Nxyz, root);
      float R = math::distance_from_origin(xyz);

      //R limite validity
      if(R < optim->axis_x.bound[0]) optim->axis_x.bound[0] = R;
      if(R > optim->axis_x.bound[1]) optim->axis_x.bound[1] = R;

      // Calculate the index of the cell in the heatmap grid
      int i = static_cast<int>((R - plot->IfRIt.axis_x.min) / (plot->IfRIt.axis_x.max - plot->IfRIt.axis_x.min) * plot->IfRIt.axis_x.size);
      int j = static_cast<int>((It - plot->IfRIt.axis_y.max) / (plot->IfRIt.axis_y.min - plot->IfRIt.axis_y.max) * plot->IfRIt.axis_y.size);
      int index = j * plot->IfRIt.axis_x.size + i;
      if(index >= 0 && index < plot->IfRIt.axis_z.size){
        plot->IfRIt.axis_z.data[index] = Is;
        sphere->data[index] = vec3(R, It, Is);
      }
    }
  }

  //---------------------------
}
void Measure::data_IfR(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::model::sphere::structure::Optimization* optim = &model_struct->sphere.optim;
  rad::model::sphere::structure::Sphere* sphere = &model_struct->sphere.sphere;
  rad::model::sphere::structure::Plot* plot = &model_struct->sphere.plot;
  //---------------------------

  //Search for closest point
  int idx = rad_struct->sphere.ransac.idx_nearest;
  float R = math::distance_from_origin(search_xyz[idx]);
  float Is = search_Is[idx];

  //Insert measure
  int index = static_cast<int>(std::round(R / plot->IfR.axis_x.resolution));
  if(index >= 0 && index < plot->IfR.axis_x.data.size()){
    plot->IfR.axis_x.data[index] = R;
    plot->IfR.axis_y.data[index] = Is;
    plot->IfR.highlight = vec2(R, Is);
    optim->axis_x.current = R;
  }

  //---------------------------
}
void Measure::data_IfIt(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::model::sphere::structure::Sphere* sphere = &model_struct->sphere.sphere;
  rad::model::sphere::structure::Plot* plot = &model_struct->sphere.plot;
  //---------------------------

  //Init parameter
  glm::vec3 root = vec3(0, 0, 0);
  glm::vec3 pose = rad_struct->sphere.ransac.current_pose;
  float diameter = rad_struct->sphere.ransac.sphere_diameter;
  float thres_sphere = rad_struct->sphere.ransac.thres_sphere;

  //Insert measure
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, pose) - diameter / 2 + 0.02;

    if(distance <= thres_sphere){
      glm::vec3 Nxyz = glm::normalize(xyz - pose);
      float Is = search_Is[i];
      float It = math::compute_It(xyz, Nxyz, root);

      //Add into model data vector
      int index = static_cast<int>(std::round(It / plot->IfIt.axis_x.resolution));
      plot->IfIt.axis_x.data[index] = It;
      plot->IfIt.axis_y.data[index] = Is;
    }
  }

  //---------------------------
}

}
