#include "Calibration.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_transfo = new k4n::utils::Transformation();
  this->k4n_glyph = new k4n::calibration::Glyph(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->ope_fitting = new ope::attribut::Fitting();
  this->map_step[k4n::calibration::WAIT_VALIDATION] = "Wait validation";
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
      this->step++;
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

    if(distance <= sensor->detection.sphere_diameter){
      sphere_xyz.push_back(xyz);
      sphere_i.push_back(vec_i[i]);
    }
  }

  //Apply least square fitting
  ope_fitting->find_sphere_in_cloud(sphere_xyz, current_pose, radius);

  k4n_glyph->draw_sphere_glyph(sensor, current_pose, radius);


  //---------------------------
}


}
