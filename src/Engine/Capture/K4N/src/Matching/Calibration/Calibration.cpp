#include "Calibration.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_transfo = new k4n::utils::Transformation();
  this->k4n_glyph = new k4n::calibration::Glyph(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();
  this->ope_normal = new ope::attribut::Normal();
  this->map_step[k4n::calibration::WAIT_VALIDATION] = "Validate";
  this->map_step[k4n::calibration::PROCESSING] = "Processing";
  this->step = k4n::calibration::WAIT_VALIDATION;

  this->radius = 0.5f;

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::next_step(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(step){
    case k4n::calibration::WAIT_VALIDATION:{
      this->validate_bbox(sensor);
      break;
    }
    case k4n::calibration::PROCESSING:{
      this->step = k4n::calibration::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Calibration::validate_bbox(k4n::dev::Sensor* sensor){
  if(sensor->detection.nb_detection == 0) return;
  if(step != k4n::calibration::WAIT_VALIDATION) return;
  //---------------------------

  this->step++;
  ivec2 point_2d = sensor->detection.vec_circle[0].center;
  vec3 truc = k4n_transfo->convert_depth_2d_to_3d(sensor, point_2d);
  vec4 machin = vec4(truc.x, truc.y, truc.z, 1);
  truc = sensor->object.pose.model * machin;
  this->current_pose = vec3(truc.x, truc.y, truc.z);

  //---------------------------
}
void Calibration::ransac_sphere(k4n::dev::Sensor* sensor){
  if(step != k4n::calibration::PROCESSING) return;
  //---------------------------

  vector<vec3>& vec_xyz = sensor->object.data.xyz;
  vector<float>& vec_i = sensor->object.data.Is;

  //Search for point inside a global sphere around current center point
  vector<vec3> sphere_xyz;
  vector<float> sphere_i;
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, current_pose);

    if(distance <= sensor->detection.sphere_diameter * k4n_struct->matching.calibration.ransac_search_diameter_x){
      sphere_xyz.push_back(xyz);
      sphere_i.push_back(vec_i[i]);
    }
  }

  //Apply least square fitting
  ope_ransac->set_num_iteration(k4n_struct->matching.calibration.ransac_nb_iter);
  ope_ransac->set_threshold_sphere(k4n_struct->matching.calibration.ransac_thres_sphere);
  ope_ransac->set_threshold_pose(k4n_struct->matching.calibration.ransac_thres_pose);
  ope_ransac->set_threshold_radius(k4n_struct->matching.calibration.ransac_thres_radius);
  ope_ransac->ransac_sphere_in_cloud(sphere_xyz, current_pose, radius, sensor->detection.sphere_diameter/2);


  k4n_glyph->draw_sphere_glyph(sensor, current_pose, radius);

  this->data_IfR(sphere_xyz, sphere_i);
  this->data_IfIt(sphere_xyz, sphere_i);



  //---------------------------
}

void Calibration::data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
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

  //ADdd into model data vector
  int index = static_cast<int>(std::round(R / k4n_struct->matching.model.IfR.x_resolution));
  if(index >= 0 && index < k4n_struct->matching.model.IfR.vec_x.size()){
    k4n_struct->matching.model.IfR.vec_x[index] = R;
    k4n_struct->matching.model.IfR.vec_y[index] = I;
  }

  //---------------------------
}
void Calibration::data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i){
  //---------------------------

  //Search for closest point
  float It = 1000.0f;
  float I = 0;
  vec3 Nxyz;
  vec3 root = vec3(0, 0, 0);
  for(int i=0; i<sphere_xyz.size(); i++){
    vec3& xyz = sphere_xyz[i];
    float distance = math::distance(xyz, current_pose) - radius;

    if(distance <= k4n_struct->matching.calibration.ransac_thres_sphere){
      I = sphere_i[i];
      Nxyz = normalize(xyz - current_pose);
      It = ope_normal->compute_It(xyz, Nxyz, root);


      //ADdd into model data vector
      int index = static_cast<int>(std::round(It / k4n_struct->matching.model.IfIt.x_resolution));
      if(index >= 0 && index < k4n_struct->matching.model.IfIt.vec_x.size()){
        k4n_struct->matching.model.IfIt.vec_x[index] = I;
        k4n_struct->matching.model.IfIt.vec_y[index] = It;
      }
    }
  }



  //---------------------------
}








}
