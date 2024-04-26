#include "Ransac.h"

#include <Operation/Fitting/Sphere.h>


namespace ope::fitting{

//Constructor / Destructor
Ransac::Ransac(){
  //---------------------------

  this->ope_sphere = new ope::fitting::Sphere();

  //---------------------------
}
Ransac::~Ransac(){}

//Ransac fitting
void Ransac::ransac_sphere_in_cloud(std::vector<vec3>& xyz, vec3& best_center, float& best_radius, float radius_to_find){
  if(xyz.size() == 0) return;
  //------------------------

  // Initialize best sphere parameters
  float best_distance = 1000;
  int best_num_inliers = 0;
  best_radius = 0.0f;

  // Seed random number generator
  srand(time(nullptr));

  // Perform RANSAC iters
  vector<Sphere> vec_sphere;
  for(int iter=0; iter<num_iter; ++iter){
    // Randomly select three points
    std::vector<vec3> sample_points;
    sample_points.reserve(50);
    for(int i=0; i<50; ++i){
      int random_index = rand() % xyz.size();
      sample_points.push_back(xyz[random_index]);
    }

    // Fit a sphere to the selected points
    vec3 center;
    float radius;
    ope_sphere->find_sphere_in_cloud(sample_points, center, radius);
    if(center == vec3(0, 0, 0) || radius == 0) continue;

    // Count inliers
    int num_inliers = 0;
    float distance = 0;
    for(const auto& point : xyz){
      float distance_to_sphere = abs(glm::distance(point, center) - radius);
      float distance_to_center = glm::distance(center, best_center);
      float distance_to_radius = abs(radius - radius_to_find);

      bool dist_sphere = distance_to_sphere < threshold_sphere;
      bool dist_center = distance_to_center < threshold_pose;
      bool dist_radius = distance_to_radius < threshold_radius;

      if(dist_sphere && dist_center && dist_radius){
        ++num_inliers;
        distance += distance_to_sphere + distance_to_center + distance_to_radius;
      }
    }

    // Update best model if current model has more inliers
    if(num_inliers > best_num_inliers && distance < best_distance){
      best_num_inliers = num_inliers;
      best_center = center;
      best_radius = radius;
      best_distance = distance;
    }
  }

  //------------------------
}

}
