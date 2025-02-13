#include "Ransac.h"

#include <Radiometry/Correction/Namespace.h>
#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor::cloud{

//Constructor / Destructor
Ransac::Ransac(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_glyph = new rad::cor::Glyph(node_correction);
  this->rad_measure = new rad::cor::Measure(node_correction);
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::ransac_sphere(dat::base::Sensor& sensor){
  static float current_timestamp = 0;
  //---------------------------

  //If no initial detection, return
  if(sensor.timestamp.current == current_timestamp) return;
  if(rad_struct->ransac.current_pose == glm::vec3(0, 0, 0)) return;
  current_timestamp = sensor.timestamp.current;

  //Search for point inside a global sphere around current center point
  this->reset_search_space();
  this->reduce_search_space(sensor);
  this->apply_ransac();
  this->apply_refinement();

  //Postprocessing stuff
  rad_glyph->draw_calibration_sphere(sensor);
  rad_measure->process_measure(sensor);

  //---------------------------
}

//Algo function
void Ransac::reset_search_space(){
  //---------------------------

  std::vector<glm::vec3>& search_xyz = rad_struct->ransac.search_xyz;
  std::vector<glm::vec3>& search_Nxyz = rad_struct->ransac.search_Nxyz;
  std::vector<float>& search_Is = rad_struct->ransac.search_Is;

  search_xyz.clear();
  search_Nxyz.clear();
  search_Is.clear();

  //---------------------------
}
void Ransac::reduce_search_space(dat::base::Sensor& sensor){
  std::vector<glm::vec3>& vec_xyz = sensor.data->xyz;
  std::vector<glm::vec3>& vec_Nxyz = sensor.data->Nxyz;
  //---------------------------

  glm::vec3 pose = rad_struct->ransac.current_pose;
  float search_radius = rad_struct->ransac.search_radius;

  //Search for point inside a global sphere around current center point
  for(int i=0; i<vec_xyz.size(); i++){
    glm::vec3& xyz = vec_xyz[i];
    glm::vec3& Nxyz = vec_Nxyz[i];
    float Is = sensor.info.buffer_ir[i];

    float distance = math::distance(xyz, pose);

    if(distance <= search_radius){
      rad_struct->ransac.search_xyz.push_back(xyz);
      rad_struct->ransac.search_Nxyz.push_back(Nxyz);
      rad_struct->ransac.search_Is.push_back(Is);
    }
  }

  //---------------------------
}
void Ransac::apply_ransac(){
  //---------------------------

  //Set parameter
  ope_ransac->set_num_iteration(1000);
  ope_ransac->set_num_sample(50);
  ope_ransac->set_threshold_sphere(rad_struct->ransac.thres_sphere);
  ope_ransac->set_threshold_radius(rad_struct->ransac.thres_radius);

  //Run ransac algorithm
  std::vector<glm::vec3>& search_xyz = rad_struct->ransac.search_xyz;
  std::vector<glm::vec3>& search_Nxyz = rad_struct->ransac.search_Nxyz;
  float sphere_radius = rad_struct->ransac.sphere_diameter / 2;
  ope_ransac->ransac_sphere(search_xyz, search_Nxyz, rad_struct->ransac.current_pose, sphere_radius);

  //---------------------------
}
void Ransac::apply_refinement(){
  //---------------------------

  std::vector<glm::vec3>& search_xyz = rad_struct->ransac.search_xyz;
  glm::vec3& pose = rad_struct->ransac.current_pose;
  float sphere_radius = rad_struct->ransac.sphere_diameter / 2;

  //Refine by getting closest point
  glm::vec3 direction = glm::normalize(pose);
  int idx = find_nearest_point(search_xyz, direction);
  glm::vec3 nearest = search_xyz[idx];
  pose = nearest + sphere_radius * glm::normalize(nearest);
  rad_struct->ransac.idx_nearest = idx;

  //---------------------------
}

//Subfunction
glm::vec3 Ransac::project_point_on_plane(const glm::vec3& point, const glm::vec3& normal){
    glm::vec3 normal_normalized = glm::normalize(normal);
    float distance = glm::dot(point, normal_normalized);
    return point - distance * normal_normalized;
}
int Ransac::find_nearest_point(const std::vector<glm::vec3>& search_xyz, const glm::vec3& center_direction){
  //---------------------------

  int idx = -1;
  float min_distance = std::numeric_limits<float>::max();
  glm::vec3 direction_normalized = glm::normalize(center_direction);

  for(int i=0; i<search_xyz.size(); i++){
    glm::vec3 xyz = search_xyz[i];

    // Project point onto the plane perpendicular to the center direction
    glm::vec3 projected_point = project_point_on_plane(xyz, direction_normalized);

    // Compute the distance from the projected point to the origin
    float distance = glm::length(projected_point);

    if(distance < min_distance){
      min_distance = distance;
      idx = i;
    }
  }

  //---------------------------
  return idx;
}


}
