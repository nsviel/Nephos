#pragma once

#include "../Base/Glyph_source.h"


namespace glyph::object{

class AABB : public Glyph_source
{
public:
  AABB();

public:
  void create_glyph();
  void update_glyph(eng::structure::Set* collection, eng::structure::Glyph* glyph);
  void update_glyph(eng::structure::Object* object);
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  int width;
};

}
