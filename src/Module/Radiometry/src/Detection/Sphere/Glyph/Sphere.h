#pragma once

#include <Data/src/Base/Glyph.h>

namespace eng{class Node;}
namespace cam{class Control;}
namespace ldr::io{class Importer;}


namespace rad::detection::glyph{

class Sphere : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Sphere(eng::Node* node_engine);
  ~Sphere();

public:
  //Main function
  void create();
  void update_pose(dat::base::Entity* entity);
  void reset_glyph();

  //Subfunction
  void construct(glm::vec4 color);
  void move_sphere(glm::vec3 pose, float diameter);

private:
  ldr::io::Importer* ldr_loader;
  cam::Control* cam_control;

  int size = 20;
  glm::mat4 mat_model = glm::mat4(1);
};

}