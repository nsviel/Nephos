#include "Detection.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_glyph = new rad::detection::cloud::Glyph(node_radio);

  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();
  this->ope_normal = new ope::attribut::Normal();
  this->map_step[rad::detection::cloud::WAIT_VALIDATION] = "Wait validation";
  this->map_step[rad::detection::cloud::PROCESSING] = "Detectioning";
  this->step = rad::detection::cloud::WAIT_VALIDATION;

  this->radius = 0.5f;

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::next_step(dat::base::Sensor* sensor){
  //---------------------------

  switch(step){
    case rad::detection::cloud::WAIT_VALIDATION:{
      this->validate_bbox(sensor);
      break;
    }
    case rad::detection::cloud::PROCESSING:{
      this->step = rad::detection::cloud::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Detection::validate_bbox(dat::base::Sensor* sensor){
  if(rad_struct->detection.nb_detection == 0) return;
  if(step != rad::detection::cloud::WAIT_VALIDATION) return;
  //---------------------------

  utl::base::Pose* pose = sensor->get_pose();

  this->step++;
  ivec2 point_2d = rad_struct->detection.vec_circle[0].center;
  vec3 truc = sensor->convert_depth_2d_to_3d(point_2d);
  vec4 machin = vec4(truc.x, truc.y, truc.z, 1);
  truc = pose->model * machin;
  this->current_pose = vec3(truc.x, truc.y, truc.z);

  //---------------------------
}
void Detection::ransac_sphere(dat::base::Sensor* sensor){
  if(step != rad::detection::cloud::PROCESSING) return;
  //---------------------------

  utl::base::Data* data = sensor->get_data();
  vector<vec3>& vec_xyz = data->xyz;
  vector<float>& vec_i = data->Is;

  //Search for point inside a global sphere around current center point
  vector<vec3> sphere_xyz;
  vector<float> sphere_i;
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, current_pose);

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
  ope_ransac->ransac_sphere_in_cloud(sphere_xyz, current_pose, radius, rad_struct->detection.sphere_diameter/2);

  //Apply post-processing stuff
  rad_glyph->draw_sphere_glyph(sensor, current_pose, radius);
  this->data_IfR(sphere_xyz, sphere_i);
  this->data_IfIt(sphere_xyz, sphere_i);
  this->data_model(sphere_xyz, sphere_i);

  //---------------------------
}

//Data function
void Detection::data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
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
  int index = static_cast<int>(std::round(R / measure->IfR.axis_x.resolution));
  if(index >= 0 && index < measure->IfR.axis_x.data.size()){
    measure->IfR.axis_x.data[index] = R;
    measure->IfR.axis_y.data[index] = I;
    measure->IfR.highlight = vec2(R, I);
    optim->axis_x.current = R;
  }

  //---------------------------
}
void Detection::data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance(xyz, current_pose) - radius;

    if(distance <= rad_struct->detection.ransac.thres_sphere){
      I = sphere_i[i];
      Nxyz = normalize(xyz - current_pose);
      It = ope_normal->compute_It(xyz, Nxyz, root);

      //Add into model data vector
      int index = static_cast<int>(std::round(It / measure->IfIt.axis_x.resolution));
      measure->IfIt.axis_x.data[index] = It;
      measure->IfIt.axis_y.data[index] = I;
    }
  }

  //---------------------------
}
void Detection::data_model(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  float R = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance(xyz, current_pose) - radius;

    if(distance <= rad_struct->detection.ransac.thres_sphere){
      I = sphere_i[i];
      Nxyz = normalize(xyz - current_pose);
      It = ope_normal->compute_It(xyz, Nxyz, root);
      R = math::distance_from_origin(xyz);

      //Search for R limite validity
      if(R < optim->axis_x.bound[0]) optim->axis_x.bound[0] = R;
      if(R > optim->axis_x.bound[1]) optim->axis_x.bound[1] = R;

      // Calculate the index of the cell in the heatmap grid
      int i = static_cast<int>((R - measure->IfRIt.axis_x.min) / (measure->IfRIt.axis_x.max - measure->IfRIt.axis_x.min) * measure->IfRIt.axis_x.size);
      int j = static_cast<int>((It - measure->IfRIt.axis_y.max) / (measure->IfRIt.axis_y.min - measure->IfRIt.axis_y.max) * measure->IfRIt.axis_y.size);
      int index = j * measure->IfRIt.axis_x.size + i;
      if(index >= 0 && index < measure->IfRIt.axis_z.size){
        measure->IfRIt.axis_z.data[index] = I;
        measure->vec_data[index] = vec3(R, It, I);
      }
    }
  }

  //---------------------------
}

}
