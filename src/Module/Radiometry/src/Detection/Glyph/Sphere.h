#pragma once

#include <Data/src/Base/Glyph.h>

namespace ope{class Transformation;}
namespace ldr::io{class Importer;}


namespace rad::detection::glyph{

class Sphere : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Sphere();
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
  ope::Transformation* ope_transform;

  int size = 20;
  glm::mat4 truc = glm::mat4(1);
};

}
