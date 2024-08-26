#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::media{class Image;}
namespace dat::base{class Sensor;}


namespace dat::img{

class Normal
{
public:
  // Constructor / Destructor
  Normal();
  ~Normal();

public:
  //Main function
  /*void compute_normal(std::shared_ptr<dat::base::Sensor> sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);

  //Method function
  void compute_normal_with_gradient(std::shared_ptr<dat::base::Sensor> sensor, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  void compute_normal_with_cov(std::shared_ptr<dat::base::Sensor> sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);
  void compute_normal_with_cov_img(std::shared_ptr<dat::base::Sensor> sensor, utl::media::Image* depth, int width, int height, std::vector<glm::vec3>& vec_Nxyz);

  //Subfunction
  void compute_neigbor(std::shared_ptr<dat::base::Sensor> sensor, std::vector<glm::vec3>& vec_nn, int x, int y, int width, int height);
*/
private:
  int k = 10;
};

}
