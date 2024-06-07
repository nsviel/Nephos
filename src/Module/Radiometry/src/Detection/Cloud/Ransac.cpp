#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Ransac::Ransac(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_glyph = new rad::detection::glyph::Manager(node_radio);
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  this->radius = 0.5f;

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::ransac_sphere(dyn::base::Sensor* sensor){
  if(rad_struct->model.sphere.state_step != rad::detection::PROCESSING) return;
  //---------------------------

  //Search for point inside a global sphere around current center point
  vector<vec3> search_xyz;
  vector<float> search_is;
  this->reduce_search_space(sensor, search_xyz, search_is);
  this->apply_ransac(search_xyz, search_is);
  this->process_result(search_xyz, search_is);

  //---------------------------
}

//Subfunction
void Ransac::reduce_search_space(dyn::base::Sensor* sensor, vector<vec3>& search_xyz, vector<float>& search_is){
  vector<vec3>& vec_xyz = sensor->data.xyz;
  vector<float>& vec_i = sensor->data.Is;
  //---------------------------

  //Search for point inside a global sphere around current center point
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, rad_struct->detection.ransac.current_pose);

    if(distance <= rad_struct->detection.sphere_diameter * rad_struct->detection.ransac.search_lambda){
      search_xyz.push_back(xyz);
      search_is.push_back(vec_i[i]);
    }
  }

  //---------------------------
}
void Ransac::apply_ransac(vector<vec3>& search_xyz, vector<float>& search_is){
  //---------------------------

  //Apply least square fitting
  ope_ransac->set_num_iteration(rad_struct->detection.ransac.nb_iter);
  ope_ransac->set_threshold_sphere(rad_struct->detection.ransac.thres_sphere);
  ope_ransac->set_threshold_pose(rad_struct->detection.ransac.thres_pose);
  ope_ransac->set_threshold_radius(rad_struct->detection.ransac.thres_radius);
  ope_ransac->ransac_sphere_in_cloud(search_xyz, rad_struct->detection.ransac.current_pose, radius, rad_struct->detection.sphere_diameter/2);

  //---------------------------
}
void Ransac::process_result(vector<vec3>& search_xyz, vector<float>& search_is){
  //---------------------------

  //Apply post-processing stuff
  rad_glyph->draw_calibration_sphere(rad_struct->detection.ransac.current_pose, radius);
  this->data_IfR(search_xyz, search_is);
  this->data_IfIt(search_xyz, search_is);
  this->data_model(search_xyz, search_is);

  //---------------------------
}

//Data function
void Ransac::data_IfR(vector<vec3>& search_xyz, vector<float>& search_is){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //Search for closest point
  float R = 1000.0f;
  float I = 0;
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance_from_origin(xyz);

    if(distance < R){
      R = distance;
      I = search_is[i];
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
void Ransac::data_IfIt(vector<vec3>& search_xyz, vector<float>& search_is){
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, rad_struct->detection.ransac.current_pose) - radius;

    if(distance <= rad_struct->detection.ransac.thres_sphere){
      I = search_is[i];
      Nxyz = normalize(xyz - rad_struct->detection.ransac.current_pose);
      It = math::compute_It(xyz, Nxyz, root);

      //Add into model data vector
      int index = static_cast<int>(std::round(It / plot->IfIt.axis_x.resolution));
      plot->IfIt.axis_x.data[index] = It;
      plot->IfIt.axis_y.data[index] = I;
    }
  }

  //---------------------------
}
void Ransac::data_model(vector<vec3>& search_xyz, vector<float>& search_is){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  float R = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<search_xyz.size(); i++){
    vec3& xyz = search_xyz[i];
    float distance = math::distance(xyz, rad_struct->detection.ransac.current_pose) - radius;

    if(distance <= rad_struct->detection.ransac.thres_sphere){
      I = search_is[i];
      Nxyz = normalize(xyz - rad_struct->detection.ransac.current_pose);
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
