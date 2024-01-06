#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Base/Namespace.h>


namespace glyph::object{

class AABB : public eng::data::Glyph
{
public:
  AABB();

public:
  //Main function
  void create(eng::data::Object* object);
  void update(eng::data::Object* object);

  //Subfunction
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  vec4 color;
};

}
