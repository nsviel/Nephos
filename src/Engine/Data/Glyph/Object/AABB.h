#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Base/Namespace.h>


namespace glyph::object{

class AABB
{
public:
  AABB();

public:
  void create(eng::structure::Object* object);
  void update(eng::structure::Object* object);
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  vec4 color;
};

}
