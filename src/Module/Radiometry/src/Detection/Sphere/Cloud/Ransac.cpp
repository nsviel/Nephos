#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Ransac::Ransac(rad::detection::Node* node_detection){
  //---------------------------

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_glyph = new rad::detection::glyph::Manager(node_detection);
  this->rad_measure = new rad::detection::cloud::Measure(node_detection);
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::ransac_sphere(dyn::base::Sensor* sensor){
  //---------------------------

  //If no initial detection, return
  if(rad_struct->sphere.ransac.current_pose == glm::vec3(0, 0, 0)) return;

  //Search for point inside a global sphere around current center point
  vector<vec3> search_xyz;
  vector<float> search_Is;
  this->reduce_search_space(sensor, search_xyz, search_Is);
  this->apply_ransac(search_xyz, search_Is);

  //Postprocessing stuff
  rad_measure->process_measure(search_xyz, search_Is);
  rad_glyph->draw_calibration_sphere(sensor, rad_struct->sphere.ransac.search_radius);

  //---------------------------
}

//Subfunction
void Ransac::reduce_search_space(dyn::base::Sensor* sensor, vector<vec3>& search_xyz, vector<float>& search_Is){
  vector<vec3>& vec_xyz = sensor->data.xyz;
  vector<float>& vec_i = sensor->data.Is;
  //---------------------------

  //Search for point inside a global sphere around current center point
  for(int i=0; i<vec_xyz.size(); i++){
    glm::vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, rad_struct->sphere.ransac.current_pose);

    if(distance <= rad_struct->sphere.ransac.sphere_diameter * rad_struct->sphere.ransac.search_lambda){
      search_xyz.push_back(xyz);
      search_Is.push_back(vec_i[i]);
    }
  }

  //---------------------------
}
void Ransac::apply_ransac(vector<vec3>& search_xyz, vector<float>& search_Is){
  //---------------------------

  //Set parameter
  ope_ransac->set_num_iteration(rad_struct->sphere.ransac.nb_iter);
  ope_ransac->set_threshold_sphere(rad_struct->sphere.ransac.thres_sphere);
  ope_ransac->set_threshold_radius(rad_struct->sphere.ransac.thres_radius);

  //Run ransac algorithm
  glm::vec3& current_pose = rad_struct->sphere.ransac.current_pose;
  float sphere_radius = rad_struct->sphere.ransac.sphere_diameter / 2;
  ope_ransac->ransac_sphere(search_xyz, current_pose, sphere_radius);

  //---------------------------
}

}
