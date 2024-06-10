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
void Ransac::ransac_sphere(const std::vector<glm::vec3>& xyz, glm::vec3& best_center, float radius){
  if(xyz.size() == 0) return;
  //------------------------

  this->init();
  this->run(xyz, best_center, radius);

  //------------------------
}

//Algorithm function
void Ransac::init(){
  //------------------------

  // Initialize best sphere parameters
  this->best_score = 1000;
  this->best_nb_inlier = 0;

  // Seed random number generator
  srand(time(nullptr));

  //------------------------
}
void Ransac::run(const std::vector<glm::vec3>& xyz, glm::vec3& best_center, float radius){
  //------------------------

  // Perform RANSAC
  for(int i=0; i<nb_iter; ++i){
    // Randomly select three points
    this->random_sample(xyz);

    // Test sample point consensus
    this->test_consensus(xyz, radius);

    // Update best model if current model has more inliers
    this->evaluate(best_center);
  }

  //------------------------
}

//Subfunction
void Ransac::random_sample(const std::vector<glm::vec3>& xyz){
  this->sample_xyz.clear();
  this->sample_xyz.reserve(nb_sample);
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
void Ransac::test_consensus(const std::vector<glm::vec3>& xyz, float known_radius){
  this->nb_inlier = 0;
  this->score = 0;
  this->center = glm::vec3(0, 0, 0);
  this->radius = 0;
  //------------------------

  //Fit sphere on sample points
  ope_sphere->find_sphere_in_cloud(sample_xyz, center, radius);
  if(center == glm::vec3(0, 0, 0) || radius == 0) return;

  //Check radius distance
  float distance_to_radius = abs(radius - known_radius);
  if(distance_to_radius > threshold_radius) return;

  // Count inliers
  for(const auto& point : xyz){
    float distance_to_sphere = abs(glm::distance(point, center) - radius);

    if(distance_to_sphere < threshold_sphere){
      this->nb_inlier++;
      this->score += distance_to_sphere + distance_to_radius;
    }
  }

  //------------------------
}
void Ransac::evaluate(glm::vec3& best_center){
  //------------------------

  if(nb_inlier > best_nb_inlier && score < best_score){
    this->best_nb_inlier = nb_inlier;
    this->best_score = score;

    best_center = center;
  }

  //------------------------
}

}
