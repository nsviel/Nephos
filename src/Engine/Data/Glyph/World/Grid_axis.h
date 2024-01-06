#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::world{

class Grid_axis : public eng::data::Glyph
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
