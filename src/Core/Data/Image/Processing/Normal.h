#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::media{class Image;}
namespace dyn::prc::base{class Sensor;}


namespace dat::img{

class Normal
{
public:
  // Constructor / Destructor
  Normal();
  ~Normal();

public:
  //Main function
  /*void compute_normal(dyn::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);

  //Method function
  void compute_normal_with_gradient(dyn::base::Sensor* sensor, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  void compute_normal_with_cov(dyn::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  void compute_normal_with_cov_img(dyn::base::Sensor* sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);

  //Subfunction
  void compute_neigbor(dyn::base::Sensor* sensor, std::vector<glm::vec3>& vec_nn, int x, int y, int width, int height);
*/
private:
  int k = 10;
};

}
