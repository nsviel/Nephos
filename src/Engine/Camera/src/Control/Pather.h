#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace cam{class Node;}
namespace cam{class Structure;}
namespace cam{class Control;}


namespace cam{

class Pather
{
public:
  Pather(cam::Node* node_camera);
  ~Pather();

public:
  //Main function
  void init();
  void make_path();

  //Subfunction
  glm::vec3 update_position(const glm::vec3& start, const glm::vec3& end, float t);

private:
  cam::Structure* cam_struct;
  cam::Control* cam_control;
};

}
