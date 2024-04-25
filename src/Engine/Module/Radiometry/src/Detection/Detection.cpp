#include "Detection.h"

#include <K4N/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio{

//Constructor / Destructor
Detection::Detection(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_transfo = new k4n::utils::Transformation();
  this->k4n_glyph = new radio::model::Glyph(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();
  this->ope_normal = new ope::attribut::Normal();
  this->map_step[radio::model::WAIT_VALIDATION] = "Wait validation";
  this->map_step[radio::model::PROCESSING] = "Processing";
  this->step = radio::model::WAIT_VALIDATION;

  this->radius = 0.5f;

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::next_step(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(step){
    case radio::model::WAIT_VALIDATION:{
      this->validate_bbox(sensor);
      break;
    }
    case radio::model::PROCESSING:{
      this->step = radio::model::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Detection::validate_bbox(k4n::dev::Sensor* sensor){
  if(sensor->detection.nb_detection == 0) return;
  if(step != radio::model::WAIT_VALIDATION) return;
  //---------------------------

  this->step++;
  ivec2 point_2d = sensor->detection.vec_circle[0].center;
  vec3 truc = k4n_transfo->convert_depth_2d_to_3d(sensor, point_2d);
  vec4 machin = vec4(truc.x, truc.y, truc.z, 1);
  truc = sensor->object.pose.model * machin;
  this->current_pose = vec3(truc.x, truc.y, truc.z);

  //---------------------------
}
void Detection::ransac_sphere(k4n::dev::Sensor* sensor){
  if(step != radio::model::PROCESSING) return;
  //---------------------------

  vector<vec3>& vec_xyz = sensor->object.data.xyz;
  vector<float>& vec_i = sensor->object.data.Is;

  //Search for point inside a global sphere around current center point
  vector<vec3> sphere_xyz;
  vector<float> sphere_i;
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, current_pose);

    if(distance <= sensor->detection.sphere_diameter * k4n_struct->radio.detection.ransac.search_diameter_x){
      sphere_xyz.push_back(xyz);
      sphere_i.push_back(vec_i[i]);
    }
  }

  //Apply least square fitting
  ope_ransac->set_num_iteration(k4n_struct->radio.detection.ransac.nb_iter);
  ope_ransac->set_threshold_sphere(k4n_struct->radio.detection.ransac.thres_sphere);
  ope_ransac->set_threshold_pose(k4n_struct->radio.detection.ransac.thres_pose);
  ope_ransac->set_threshold_radius(k4n_struct->radio.detection.ransac.thres_radius);
  ope_ransac->ransac_sphere_in_cloud(sphere_xyz, current_pose, radius, sensor->detection.sphere_diameter/2);

  //Apply post-processing stuff
  k4n_glyph->draw_sphere_glyph(sensor, current_pose, radius);
  this->data_IfR(sphere_xyz, sphere_i);
  this->data_IfIt(sphere_xyz, sphere_i);
  this->data_model(sphere_xyz, sphere_i);

  //---------------------------
}

//Data function
void Detection::data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  radio::structure::Optimization* model = &k4n_struct->radio.model.optim;
  radio::structure::Measure* measure = &k4n_struct->radio.model.measure;
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
  int index = static_cast<int>(std::round(R / measure->IfR.x.resolution));
  if(index >= 0 && index < measure->IfR.x.data.size()){
    measure->IfR.x.data[index] = R;
    measure->IfR.y.data[index] = I;
    measure->IfR.highlight = vec2(R, I);
    model->x.current = R;
  }

  //---------------------------
}
void Detection::data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  radio::structure::Measure* measure = &k4n_struct->radio.model.measure;
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance(xyz, current_pose) - radius;

    if(distance <= k4n_struct->radio.detection.ransac.thres_sphere){
      I = sphere_i[i];
      Nxyz = normalize(xyz - current_pose);
      It = ope_normal->compute_It(xyz, Nxyz, root);

      //ADdd into model data vector
      int index = static_cast<int>(std::round(It / measure->IfIt.x.resolution));
      measure->IfIt.x.data[index] = It;
      measure->IfIt.y.data[index] = I;
    }
  }

  //---------------------------
}
void Detection::data_model(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  radio::structure::Optimization* model = &k4n_struct->radio.model.optim;
  radio::structure::Measure* measure = &k4n_struct->radio.model.measure;
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

    if(distance <= k4n_struct->radio.detection.ransac.thres_sphere){
      I = sphere_i[i];
      Nxyz = normalize(xyz - current_pose);
      It = ope_normal->compute_It(xyz, Nxyz, root);
      R = math::distance_from_origin(xyz);

      //Search for R limite validity
      if(R < model->x.bound[0]) model->x.bound[0] = R;
      if(R > model->x.bound[1]) model->x.bound[1] = R;

      // Calculate the index of the cell in the heatmap grid
      int i = static_cast<int>((R - measure->IfRIt.x.min) / (measure->IfRIt.x.max - measure->IfRIt.x.min) * measure->IfRIt.x.size);
      int j = static_cast<int>((It - measure->IfRIt.y.max) / (measure->IfRIt.y.min - measure->IfRIt.y.max) * measure->IfRIt.y.size);
      int index = j * measure->IfRIt.x.size + i;
      if(index >= 0 && index < measure->IfRIt.z.size){
        measure->IfRIt.z.data[index] = I;
        measure->vec_data[index] = vec3(R, It, I);
      }
    }
  }

  //---------------------------
}

}
