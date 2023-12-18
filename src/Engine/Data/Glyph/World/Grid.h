#pragma once

#include "../Base/Glyph_source.h"


namespace glyph::world{

class Grid : public Glyph_source
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  void create_glyph();
  void update_grid(int value);

private:
  vec4 grid_color;
  int nb_cell;
};

}
