#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}


namespace ope{

class Triangulation
{
public:
  // Constructor / Destructor
  Triangulation();
  ~Triangulation();

public:
  //Main function
  void make_triangulation(utl::base::Data* data);
  void compute_normal_from_grid(utl::base::Data* data);
  void compute_normal_with_neighbors(utl::base::Data* data, int k);

  //Subfunction
  void compute_knn(glm::vec3& point, std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, int knn, utl::base::Data* data, int i, int j, float threshold);

private:

};

}
