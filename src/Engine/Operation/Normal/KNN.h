#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}
namespace dat::base{class Object;}


namespace ope::normal{

class KNN
{
public:
  // Constructor / Destructor
  KNN();
  ~KNN();

public:
  //Main function
  void compute_normal(utl::base::Data* data);

  //Subfunction
  void compute_knn(std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, glm::vec3& point, utl::base::Data* data, int i, int j);
  void set_visibility(dat::base::Object* object, bool value);

private:
  float R_thres;
  int k;
};

}
