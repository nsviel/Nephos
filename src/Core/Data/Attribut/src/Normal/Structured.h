#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <thread>

namespace utl::base{class Data;}
namespace dat::base{class Entity;}
namespace dat::img{class Converter;}


namespace dat::atr::normal{

class Structured
{
public:
  // Constructor / Destructor
  Structured();
  ~Structured();

public:
  //Main function
  void compute_normal(utl::base::Data* data);

  //Subfunction
  void compute_knn(std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, glm::vec3& point, utl::base::Data* data, int i, int j);

  inline float get_time(){return time;}
  inline void set_knn(int value){this->k = value;}

private:
  dat::img::Converter* img_converter;

  float R_thres;
  float time;
  int k;
};

}
