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
void Ransac::ransac_sphere_in_cloud(std::vector<vec3>& xyz, vec3& best_center, float& best_radius, int num_iter, float inlier_threshold, float radius_to_find){
  if(xyz.size() == 0) return;
  //------------------------

  // Initialize best sphere parameters
  int best_num_inliers = 0;
  best_radius = 0.0f;

  // Seed random number generator
  srand(time(nullptr));

  int nb_dist_sphere = 0;
  int nb_dist_center = 0;
  int nb_dist_radius = 0;

  // Perform RANSAC iters
  for(int iter=0; iter<num_iter; ++iter){
    // Randomly select three points
    std::vector<vec3> sample_points;
    sample_points.reserve(10);
    for(int i=0; i<10; ++i){
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
    for(const auto& point : xyz){
      float distance_to_sphere = glm::distance(point, center) - radius;
      float distance_to_center = glm::distance(center, best_center);
      float distance_to_radius = glm::distance(radius, radius_to_find);

      bool dist_sphere = abs(distance_to_sphere) < 0.01;
      bool dist_center = distance_to_center < 0.01;
      bool dist_radius = distance_to_radius < 0.01;

      if(dist_sphere) nb_dist_sphere++;
      if(dist_center) nb_dist_center++;
      if(dist_radius) nb_dist_radius++;

      if(dist_sphere && dist_center && dist_radius){
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

  say("-----");
  say(best_num_inliers);
  say(nb_dist_sphere);
  say(nb_dist_center);
  say(nb_dist_radius);

  //------------------------
}

}
