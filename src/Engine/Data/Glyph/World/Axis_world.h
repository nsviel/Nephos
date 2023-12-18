#pragma once

#include "../Base/Glyph_source.h"


namespace glyph::world{

class Axis_world : public Glyph_source
{
public:
  //Constructor / Destructor
  Axis_world();
  ~Axis_world();

public:
  void create_glyph();

  inline bool* get_axis_subset_visibility(){return &is_visible;}

private:
  bool is_visible;
};

}
