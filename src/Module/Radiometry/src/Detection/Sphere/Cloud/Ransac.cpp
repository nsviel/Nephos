#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Ransac::Ransac(rad::detection::Node* node_detection){
  //---------------------------

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_glyph = new rad::detection::sphere::Glyph(node_detection);
  this->rad_measure = new rad::detection::cloud::Measure(node_detection);
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::ransac_sphere(dyn::base::Sensor* sensor){
  static float current_timestamp = 0;
  //---------------------------

  //If no initial detection, return
  if(sensor->timestamp.current == current_timestamp) return;
  if(rad_struct->sphere.ransac.current_pose == glm::vec3(0, 0, 0)) return;
  current_timestamp = sensor->timestamp.current;

  //Search for point inside a global sphere around current center point
  this->reset_search_space();
  this->reduce_search_space(sensor);
  this->apply_ransac();

  //Postprocessing stuff
  rad_measure->process_measure();
  rad_glyph->draw_calibration_sphere(sensor);

  //---------------------------
}

//Subfunction
void Ransac::reset_search_space(){
  //---------------------------

  vector<vec3>& search_xyz = rad_struct->sphere.ransac.search_xyz;
  vector<vec3>& search_Nxyz = rad_struct->sphere.ransac.search_Nxyz;
  vector<float>& search_Is = rad_struct->sphere.ransac.search_Is;

  search_xyz.clear();
  search_Nxyz.clear();
  search_Is.clear();

  //---------------------------
}
void Ransac::reduce_search_space(dyn::base::Sensor* sensor){
  vector<vec3>& vec_xyz = sensor->data.xyz;
  vector<vec3>& vec_Nxyz = sensor->data.Nxyz;
  //---------------------------

  glm::vec3 pose = rad_struct->sphere.ransac.current_pose;
  float search_radius = rad_struct->sphere.ransac.search_radius;

  //Search for point inside a global sphere around current center point
  for(int i=0; i<vec_xyz.size(); i++){
    glm::vec3& xyz = vec_xyz[i];
    glm::vec3& Nxyz = vec_Nxyz[i];
    float Is = sensor->buffer_ir[i];

    float distance = math::distance(xyz, pose);

    if(distance <= search_radius){
      rad_struct->sphere.ransac.search_xyz.push_back(xyz);
      rad_struct->sphere.ransac.search_Nxyz.push_back(Nxyz);
      rad_struct->sphere.ransac.search_Is.push_back(Is);
    }
  }

  //---------------------------
}
void Ransac::apply_ransac(){
  //---------------------------

  //Set parameter
  ope_ransac->set_num_iteration(rad_struct->sphere.ransac.nb_iter);
  ope_ransac->set_num_sample(50);
  ope_ransac->set_threshold_sphere(rad_struct->sphere.ransac.thres_sphere);
  ope_ransac->set_threshold_radius(rad_struct->sphere.ransac.thres_radius);

  //Run ransac algorithm
  std::vector<glm::vec3>& search_xyz = rad_struct->sphere.ransac.search_xyz;
  std::vector<glm::vec3>& search_Nxyz = rad_struct->sphere.ransac.search_Nxyz;
  std::vector<float>& search_Is = rad_struct->sphere.ransac.search_Is;
  glm::vec3& current_pose = rad_struct->sphere.ransac.current_pose;
  float sphere_radius = rad_struct->sphere.ransac.sphere_diameter / 2;
  ope_ransac->ransac_sphere(search_xyz, search_Nxyz, current_pose, sphere_radius);

  //---------------------------
}

}
