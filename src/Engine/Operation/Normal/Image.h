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
  void compute_normal_from_image(dat::base::Sensor* sensor, int width, int height, std::vector<glm::vec3>& vec_Nxyz);

private:

};

}
