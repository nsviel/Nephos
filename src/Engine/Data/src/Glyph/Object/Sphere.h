#pragma once

#include <Data/src/Base/Glyph.h>

namespace ope{class Transformation;}
namespace ldr{class Loader;}


namespace dat::glyph::object{

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
  void construct(vec4 color);
  void move_sphere(vec3 pose, float diameter);

private:
  ldr::Loader* ldr_loader;
  ope::Transformation* ope_transform;

  int size = 20;
  mat4 truc = mat4(1);
};

}
