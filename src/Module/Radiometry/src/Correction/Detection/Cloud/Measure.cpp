#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::correction::cloud{

//Constructor / Destructor
Measure::Measure(rad::correction::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();

  //---------------------------
}
Measure::~Measure(){}

//Main function
void Measure::process_measure(){
  //---------------------------

  vector<vec3>& search_xyz = rad_struct->ransac.search_xyz;
  vector<float>& search_Is = rad_struct->ransac.search_Is;
  rad_struct->state_data = rad::correction::HAS_DATA;

  this->data_measure(search_xyz, search_Is);
  this->data_IfR(search_xyz, search_Is);
  this->data_IfIt(search_xyz, search_Is);

  //---------------------------
}

//Subfunction
void Measure::data_measure(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
  rad::correction::structure::Measure* sphere = &rad_struct->measure;
  rad::correction::structure::Plot* plot = &rad_struct->plot;
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
  rad::correction::structure::Optimization* optim = &rad_struct->optim;
  rad::correction::structure::Measure* sphere = &rad_struct->measure;
  rad::correction::structure::Plot* plot = &rad_struct->plot;
  //---------------------------

  //Search for closest point
  int idx = rad_struct->ransac.idx_nearest;
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
  rad::correction::structure::Measure* sphere = &rad_struct->measure;
  rad::correction::structure::Plot* plot = &rad_struct->plot;
  //---------------------------

  //Init parameter
  glm::vec3 root = vec3(0, 0, 0);
  glm::vec3 pose = rad_struct->ransac.current_pose;
  float radius = rad_struct->ransac.sphere_diameter / 2;
  float thres_sphere = rad_struct->ransac.thres_sphere;

  plot->IfIt.axis_x.data = vector<float>(plot->IfIt.axis_x.data.size(), 0.0f);
  plot->IfIt.axis_y.data = vector<float>(plot->IfIt.axis_y.data.size(), 0.0f);

  //Insert measure
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, pose) - radius - 0.04;

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
