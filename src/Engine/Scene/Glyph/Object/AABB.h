#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Entity/Namespace.h>


namespace glyph::object{

class AABB : public eng::data::Glyph
{
public:
  AABB();
  ~AABB();

public:
  //Main function
  void create();
  void update_glyph(eng::data::Entity* entity);

  //Subfunction
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  vec4 color;
};

}
