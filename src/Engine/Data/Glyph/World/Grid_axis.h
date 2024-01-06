#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::world{

class Grid_axis : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Grid_axis();
  ~Grid_axis();

public:
  //Main function
  eng::data::Object* create();
  void update();

private:
  vec4 color;
  int nb_cell;
};

}
