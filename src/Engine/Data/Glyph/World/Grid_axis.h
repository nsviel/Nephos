#pragma once

#include "../Base/Source.h"


namespace glyph::world{

class Grid_axis : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Grid_axis();
  ~Grid_axis();

public:
  //Main function
  void create();
  void update();

private:
  vec4 color;
  int nb_cell;
};

}
