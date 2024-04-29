#pragma once

#include <Glyph/Control/Glyph.h>

namespace ope{class Transformation;}
namespace sce{class Loader;}


namespace gly::element::object{

class Sphere : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Sphere(eng::Node* node_engine);
  ~Sphere();

public:
  //Main function
  void create();
  void update_pose(utl::type::Entity* entity);
  void reset_glyph();

  //Subfunction
  void construct(vec4 color);
  void move_sphere(vec3 pose, float diameter);

private:
  sce::Loader* sce_loader;
  ope::Transformation* ope_transform;

  int size = 20;
  mat4 truc = mat4(1);
};

}
