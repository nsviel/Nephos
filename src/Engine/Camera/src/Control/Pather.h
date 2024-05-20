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
  void loop();

  //Subfunction
  void make_sin_wheel();
  float update_position(const float& start, const float& end, float t);

private:
  cam::Structure* cam_struct;
  cam::Control* cam_control;
};

}
