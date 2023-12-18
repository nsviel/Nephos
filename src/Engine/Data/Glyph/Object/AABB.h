#pragma once

#include "../Base/Source.h"


namespace glyph::object{

class AABB : public glyph::base::Source
{
public:
  AABB();

public:
  void create();
  void update(eng::structure::Set* collection, eng::structure::Glyph* glyph);
  void update(eng::structure::Object* object);
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  int width;
};

}
