#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::media{class Image;}
namespace dat::base{class Sensor;}


namespace ope::normal{

class Image
{
public:
  // Constructor / Destructor
  Image();
  ~Image();

public:
  //Main function
  void compute_normal_from_image(dat::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);

  //Method function
  void compute_normal_with_gradient(dat::base::Sensor* sensor, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  void compute_normal_with_cov(dat::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  void compute_normal_with_cov_img(dat::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  
  //Subfunction
  void compute_neigbor(dat::base::Sensor* sensor, std::vector<glm::vec3>& vec_nn, int x, int y, int width, int height);

private:
  int k = 10;
};

}
