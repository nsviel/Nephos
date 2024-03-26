#include "Ransac.h"

#include <Operation/src/Fitting/Sphere.h>


namespace ope::fitting{

//Constructor / Destructor
Ransac::Ransac(){
  //---------------------------

  this->ope_sphere = new ope::fitting::Sphere();

  //---------------------------
}
Ransac::~Ransac(){}

//Ransac fitting
void Ransac::ransac_sphere_in_cloud(std::vector<vec3>& xyz, vec3& best_center, float& best_radius, int num_iter, float inlier_threshold){
  //------------------------

  // Initialize best sphere parameters
  int best_num_inliers = 0;
  best_radius = 0.0f;

  // Seed random number generator
  srand(time(nullptr));

  // Perform RANSAC iters
  for(int iter=0; iter<num_iter; ++iter){
    // Randomly select three points
    std::vector<vec3> sample_points;
    sample_points.reserve(3);
    for (int i = 0; i < 3; ++i) {
      int random_index = rand() % xyz.size();
      sample_points.push_back(xyz[random_index]);
    }

    // Fit a sphere to the selected points
    vec3 center;
    float radius;
    ope_sphere->find_sphere_in_cloud(sample_points, center, radius);

    // Count inliers
    int num_inliers = 0;
    for(const auto& point : xyz){
      float distance_to_sphere = glm::distance(point, center) - radius;
      if(distance_to_sphere < inlier_threshold){
        ++num_inliers;
      }
    }

    // Update best model if current model has more inliers
    if(num_inliers > best_num_inliers){
      best_num_inliers = num_inliers;
      best_center = center;
      best_radius = radius;
    }
  }

  //------------------------
}

}
