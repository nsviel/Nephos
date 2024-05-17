#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}
namespace dat::base{class Object;}


namespace ope::attribut{

class Normal
{
public:
  // Constructor / Destructor
  Normal();
  ~Normal();

public:
  //Main function
  void compute_normal_from_grid(utl::base::Data* data);
  void compute_normal_with_neighbors(utl::base::Data* data, int k);
  void set_visibility(dat::base::Object* object, bool value);

  //Subfunction
  void compute_knn(glm::vec3& point, std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, int knn, utl::base::Data* data, int i, int j, float threshold);
  glm::mat3 compute_covariance(const std::vector<glm::vec3>& points);
  glm::vec3 compute_normal_from_covariance(const glm::mat3& covariance);
  void compute_normal_orientation(glm::vec3& normal, const glm::vec3& point);

  //Incidence angle
  float compute_cosIt(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root);
  float compute_It(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root);

private:

};

}
