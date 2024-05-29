#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Ransac::Ransac(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_glyph = new rad::detection::cloud::Glyph(node_radio);
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  this->radius = 0.5f;

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::ransac_sphere(dat::base::Sensor* sensor){
  //if(step != rad::detection::PROCESSING) return;
  //---------------------------

  utl::base::Data* data = sensor->get_data();
  vector<vec3>& vec_xyz = data->xyz;
  vector<float>& vec_i = data->Is;

  //Search for point inside a global sphere around current center point
  vector<vec3> sphere_xyz;
  vector<float> sphere_i;
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, rad_struct->detection.ransac.current_pose);

    if(distance <= rad_struct->detection.sphere_diameter * rad_struct->detection.ransac.search_diameter_x){
      sphere_xyz.push_back(xyz);
      sphere_i.push_back(vec_i[i]);
    }
  }

  //Apply least square fitting
  ope_ransac->set_num_iteration(rad_struct->detection.ransac.nb_iter);
  ope_ransac->set_threshold_sphere(rad_struct->detection.ransac.thres_sphere);
  ope_ransac->set_threshold_pose(rad_struct->detection.ransac.thres_pose);
  ope_ransac->set_threshold_radius(rad_struct->detection.ransac.thres_radius);
  ope_ransac->ransac_sphere_in_cloud(sphere_xyz, rad_struct->detection.ransac.current_pose, radius, rad_struct->detection.sphere_diameter/2);

  //Apply post-processing stuff
  rad_glyph->draw_sphere_glyph(rad_struct->detection.ransac.current_pose, radius);
  this->data_IfR(sphere_xyz, sphere_i);
  this->data_IfIt(sphere_xyz, sphere_i);
  this->data_model(sphere_xyz, sphere_i);

  //---------------------------
}

//Data function
void Ransac::data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //Search for closest point
  float R = 1000.0f;
  float I = 0;
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance_from_origin(xyz);

    if(distance < R){
      R = distance;
      I = sphere_i[i];
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
void Ransac::data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance(xyz, rad_struct->detection.ransac.current_pose) - radius;

    if(distance <= rad_struct->detection.ransac.thres_sphere){
      I = sphere_i[i];
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
void Ransac::data_model(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  float R = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance(xyz, rad_struct->detection.ransac.current_pose) - radius;

    if(distance <= rad_struct->detection.ransac.thres_sphere){
      I = sphere_i[i];
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
        measure->data[index] = vec3(R, It, I);
      }
    }
  }

  //---------------------------
}

}
