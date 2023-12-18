#pragma once

#include "../Base/Source.h"


namespace glyph::world{

class Grid : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  void create();
  void update_grid(int value);

private:
  vec4 grid_color;
  int nb_cell;
};

}
