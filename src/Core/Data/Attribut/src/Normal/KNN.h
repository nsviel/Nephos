#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}
namespace dat::base{class Object;}


namespace dat::atr::normal{

class KNN
{
public:
  // Constructor / Destructor
  KNN();
  ~KNN();

public:
  //Main function
  void compute_normal(utl::base::Data* data, int k);

  //Subfunction
  void compute_knn(std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, glm::vec3& point, utl::base::Data* data, int i, int j);

  inline float get_time(){return time;}

private:
  float R_thres;
  float time;
  int k;
};

}
