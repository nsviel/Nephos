#pragma once

#include "../Base/Source.h"


namespace glyph::object{

class AABB : public glyph::base::Source
{
public:
  AABB();

public:
  void create(eng::structure::Cloud* cloud);
  void update(eng::structure::Cloud* cloud);
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  int width;
};

}
