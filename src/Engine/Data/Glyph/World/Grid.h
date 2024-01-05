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
  //Main function
  void create();

  //Subfunction
  void construct_grid();

private:
  vec4 grid_color;
  int nb_cell;
};

}
