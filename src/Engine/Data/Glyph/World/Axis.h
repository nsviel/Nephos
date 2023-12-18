#pragma once

#include "../Base/Glyph_source.h"


namespace glyph::world{

class Axis : public Glyph_source
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  void create();

  inline bool* get_axis_subset_visibility(){return &is_visible;}

private:
  bool is_visible;
};

}
