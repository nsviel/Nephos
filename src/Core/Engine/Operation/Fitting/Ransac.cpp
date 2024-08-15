#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
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
void Ransac::ransac_sphere(const std::vector<glm::vec3>& xyz, const std::vector<glm::vec3>& Nxyz, glm::vec3& pose, float radius){
  //------------------------

  if(xyz.size() == 0){
    //cout<<"[error] no point given to ransac"<<std::endl;
    return;
  }
  if(xyz.size() != Nxyz.size()){
    std::cout<<"[error] location and normal size"<<std::endl;
    return;
  }

  // Initialize best sphere parameters
  this->best_score = 1000;
  this->best_nb_inlier = 0;
  this->best_center = glm::vec3(0, 0, 0);

  // Perform RANSAC
  for(int i=0; i<nb_iter; ++i){
    this->reset_variable();

    // Randomly select three points
    this->random_sample(xyz);

    // Test sample point consensus
    this->test_consensus(pose, xyz, Nxyz, radius);

    // Update best model if current model has more inliers
    this->evaluate(pose);
  }

  if(best_center != glm::vec3(0, 0, 0)){
    pose = best_center;
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
void Ransac::test_consensus(glm::vec3 pose, const std::vector<glm::vec3>& xyz, const std::vector<glm::vec3>& Nxyz, float known_radius){
  //------------------------

  //Fit sphere on sample points
  ope_sphere->find_sphere_in_cloud(sample_xyz, center, radius);
  if(center == glm::vec3(0, 0, 0) || radius == 0) return;
  float dist_radius = abs(radius - known_radius);
  if(dist_radius > 0.2) return;

  // Count inliers
  for(int i=0; i<xyz.size(); i++){
    glm::vec3 point = xyz[i];
    glm::vec3 normal = Nxyz[i];

    //Compare pre-calculated normal with sample one
    glm::vec3 sphere_normal = glm::normalize(point - center);
    bool same_sense = math::normal_same_sense(normal - point, sphere_normal - point);

    //Compute and compare distance of the current sample point
    float dist_angle = math::calculate_angle(normal - point, sphere_normal - point);
    float dist_sphere = abs(glm::distance(point, center) - radius);
    float dist_pose = abs(glm::distance(pose, center));

    if(same_sense && dist_sphere < threshold_sphere){
      this->nb_inlier++;
      this->score += dist_sphere + dist_pose + dist_radius + dist_angle;
    }
  }

  //------------------------
}
void Ransac::evaluate(glm::vec3& best_center){
  if(center == glm::vec3(0, 0, 0)) return;
  //------------------------

  if(score != 0 && nb_inlier > best_nb_inlier && score < best_score){
    this->best_nb_inlier = nb_inlier;
    this->best_score = score;
    this->best_center = center;
  }

  //------------------------
}


}
