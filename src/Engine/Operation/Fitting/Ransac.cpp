#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Operation/Fitting/Sphere.h>
#include <cstdlib> // for srand
#include <ctime>   // for time and time_t
#include <random>


namespace ope::fitting{

//Constructor / Destructor
Ransac::Ransac(){
  //---------------------------

  this->ope_sphere = new ope::fitting::Sphere();

  //---------------------------
}
Ransac::~Ransac(){}

//Ransac fitting
void Ransac::ransac_sphere(const std::vector<glm::vec3>& xyz, const std::vector<glm::vec3>& Nxyz, glm::vec3& best_center, float radius){
  //------------------------

  if(xyz.size() == 0){
    cout<<"[error] no point given to ransac"<<endl;
    return;
  }
  if(xyz.size() != Nxyz.size()){
    cout<<"[error] location and normal size"<<endl;
    return;
  }

  // Initialize best sphere parameters
  this->best_score = 1000;
  this->best_nb_inlier = 0;

  // Perform RANSAC
  for(int i=0; i<nb_iter; ++i){
    this->reset_variable();

    // Randomly select three points
    this->random_sample(xyz);

    // Test sample point consensus
    this->test_consensus(xyz, Nxyz, radius);

    // Update best model if current model has more inliers
    this->evaluate(best_center);
  }

  //------------------------
}

//Subfunction
void Ransac::reset_variable(){
  //------------------------

  this->sample_xyz.clear();
  this->sample_xyz.reserve(nb_sample);

  this->nb_inlier = 0;
  this->score = 0;
  this->center = glm::vec3(0, 0, 0);
  this->radius = 0;

  //------------------------
}
void Ransac::random_sample(const std::vector<glm::vec3>& xyz){
  //------------------------

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, xyz.size() - 1);

  for(int i=0; i<nb_sample; ++i){
    int random_index = dis(gen);
    this->sample_xyz.push_back(xyz[random_index]);
  }

  //------------------------
}
void Ransac::test_consensus(const std::vector<glm::vec3>& search_xyz, const std::vector<glm::vec3>& search_Nxyz, float known_radius){
  //------------------------

  //Fit sphere on sample points
  ope_sphere->find_sphere_in_cloud(sample_xyz, center, radius);
  if(center == glm::vec3(0, 0, 0) || radius == 0) return;
  if(abs(radius - known_radius) > threshold_radius) return;

  // Count inliers
  for(int i=0; i<search_xyz.size(); i++){
    glm::vec3 xyz = search_xyz[i];
    glm::vec3 Nxyz = search_Nxyz[i];

    //Compare pre-calculated normal with sample one
    glm::vec3 sphere_Nxyz = glm::normalize(xyz - center);
    bool same_direction = math::normal_same_direction(Nxyz, sphere_Nxyz);
    float angle = math::calculate_angle(Nxyz, sphere_Nxyz);

    //Compute and compare distance of the current sample point
    float distance_to_sphere = abs(glm::distance(xyz, center) - known_radius);say(angle);
    if(same_direction && distance_to_sphere < threshold_sphere && angle < 45){
      this->nb_inlier++;
      this->score += distance_to_sphere;
    }
  }

  //------------------------
}
void Ransac::evaluate(glm::vec3& best_center){
  if(center == glm::vec3(0, 0, 0)) return;
  //------------------------

  if(nb_inlier > best_nb_inlier){
    this->best_nb_inlier = nb_inlier;
    this->best_score = score;

    best_center = center;
  }

  //------------------------
}


}
