#pragma once

#include <Utility/Base/Entity/Glyph.h>

namespace ope{class Transformation;}
namespace eng::scene{class Loader;}


namespace glyph::scene{

class Sphere : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Sphere(eng::Node* node_engine);
  ~Sphere();

public:
  //Main function
  void create();
  void update_glyph();
  void reset_glyph();

  //Subfunction
  void move_sphere(vec3 pose);

private:
  eng::scene::Loader* sce_loader;
  ope::Transformation* ope_transform;

  int size = 20;
};

}
