#pragma once

#include "../Base/Glyph_source.h"


class AABB : public Glyph_source
{
public:
  AABB();

public:
/*  void create_glyph();
  void update_glyph(data::Set* collection, data::Glyph* glyph);
  void update_glyph(data::Object* object);
  vector<vec3> build_box(vec3 min, vec3 max);*/

private:
  int width;
};
