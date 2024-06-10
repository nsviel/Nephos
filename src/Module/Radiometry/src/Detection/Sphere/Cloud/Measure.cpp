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
  this->detection_struct = node_detection->get_rad_struct();

  //---------------------------
}
Measure::~Measure(){}

//Main function
void Measure::process_measure(vector<vec3>& search_xyz, vector<float>& search_Is){
  //---------------------------

  detection_struct->sphere.state_data = rad::detection::HAS_DATA;
  
  this->data_IfR(search_xyz, search_Is);
  this->data_IfIt(search_xyz, search_Is);
  this->data_model(search_xyz, search_Is);

  //---------------------------
}

//Subfunction
void Measure::data_IfR(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::model::structure::Optimization* optim = &model_struct->optim;
  rad::model::structure::Sphere* sphere = &model_struct->sphere;
  rad::model::structure::Plot* plot = &model_struct->plot;
  //---------------------------

  //Search for closest point
  float R = 1000.0f;
  float I = 0;
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance_from_origin(xyz);

    if(distance < R){
      R = distance;
      I = search_Is[i];
    }
  }

  //Add into model data vector
  int index = static_cast<int>(std::round(R / plot->IfR.axis_x.resolution));
  if(index >= 0 && index < plot->IfR.axis_x.data.size()){
    plot->IfR.axis_x.data[index] = R;
    plot->IfR.axis_y.data[index] = I;
    plot->IfR.highlight = vec2(R, I);
    optim->axis_x.current = R;
  }

  //---------------------------
}
void Measure::data_IfIt(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::model::structure::Sphere* sphere = &model_struct->sphere;
  rad::model::structure::Plot* plot = &model_struct->plot;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, detection_struct->sphere.ransac.current_pose) - detection_struct->sphere.ransac.search_radius;

    if(distance <= detection_struct->sphere.ransac.thres_sphere){
      I = search_Is[i];
      Nxyz = normalize(xyz - detection_struct->sphere.ransac.current_pose);
      It = math::compute_It(xyz, Nxyz, root);

      //Add into model data vector
      int index = static_cast<int>(std::round(It / plot->IfIt.axis_x.resolution));
      plot->IfIt.axis_x.data[index] = It;
      plot->IfIt.axis_y.data[index] = I;
    }
  }

  //---------------------------
}
void Measure::data_model(vector<vec3>& search_xyz, vector<float>& search_Is){
  rad::model::structure::Optimization* optim = &model_struct->optim;
  rad::model::structure::Sphere* sphere = &model_struct->sphere;
  rad::model::structure::Plot* plot = &model_struct->plot;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  float R = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, detection_struct->sphere.ransac.current_pose) - detection_struct->sphere.ransac.search_radius;

    if(distance <= detection_struct->sphere.ransac.thres_sphere){
      I = search_Is[i];
      Nxyz = normalize(xyz - detection_struct->sphere.ransac.current_pose);
      It = math::compute_It(xyz, Nxyz, root);
      R = math::distance_from_origin(xyz);

      //Search for R limite validity
      if(R < optim->axis_x.bound[0]) optim->axis_x.bound[0] = R;
      if(R > optim->axis_x.bound[1]) optim->axis_x.bound[1] = R;

      // Calculate the index of the cell in the heatmap grid
      int i = static_cast<int>((R - plot->IfRIt.axis_x.min) / (plot->IfRIt.axis_x.max - plot->IfRIt.axis_x.min) * plot->IfRIt.axis_x.size);
      int j = static_cast<int>((It - plot->IfRIt.axis_y.max) / (plot->IfRIt.axis_y.min - plot->IfRIt.axis_y.max) * plot->IfRIt.axis_y.size);
      int index = j * plot->IfRIt.axis_x.size + i;
      if(index >= 0 && index < plot->IfRIt.axis_z.size){
        plot->IfRIt.axis_z.data[index] = I;
        sphere->data[index] = vec3(R, It, I);
      }
    }
  }

  //---------------------------
}

}
