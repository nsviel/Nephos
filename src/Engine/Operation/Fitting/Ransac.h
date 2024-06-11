#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ope::fitting{class Sphere;}


namespace ope::fitting{

class Ransac
{
public:
  Ransac();
  ~Ransac();

public:
  //Ransac fitting
  void ransac_sphere(const std::vector<glm::vec3>& xyz, glm::vec3& center, float radius);

  inline void set_num_iteration(int value){this->nb_iter = value;}
  inline void set_num_sample(int value){this->nb_sample = value;}
  inline void set_threshold_sphere(float value){this->threshold_sphere = value;}
  inline void set_threshold_radius(float value){this->threshold_radius = value;}

private:
  void random_sample(const std::vector<glm::vec3>& xyz);
  void test_consensus(const std::vector<glm::vec3>& xyz, float radius);
  void evaluate(glm::vec3& best_center);

private:
  ope::fitting::Sphere* ope_sphere;

  //Parameter
  float threshold_sphere = 0.2;
  float threshold_radius = 0.02;
  int nb_iter = 100;
  int nb_sample = 50;

  //Variable
  std::vector<glm::vec3> sample_xyz;
  glm::vec3 center;
  float best_score = 1000;
  float radius;
  float score;
  int best_nb_inlier = 0;
  int nb_inlier = 0;
};

}
