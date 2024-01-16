#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Namespace.h>


namespace glyph::object{

class AABB : public entity::Glyph
{
public:
  AABB(Engine* engine);
  ~AABB();

public:
  //Main function
  void create();
  void update_glyph(entity::Entity* entity);

  //Subfunction
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  vec4 color;
};

}
