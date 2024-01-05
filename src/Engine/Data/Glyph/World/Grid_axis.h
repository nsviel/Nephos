#pragma once

#include <Engine/Base/Source.h>


namespace glyph::world{

class Grid_axis : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Grid_axis();
  ~Grid_axis();

public:
  //Main function
  eng::structure::Glyph* create();
  void update();

private:
  vec4 color;
  int nb_cell;
};

}
