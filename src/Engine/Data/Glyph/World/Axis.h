#pragma once

#include "../Base/Source.h"


namespace glyph::world{

class Axis : public glyph::base::Source
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
