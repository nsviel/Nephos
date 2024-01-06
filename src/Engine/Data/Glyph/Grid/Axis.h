#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::grid{

class Axis : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create();
  void update();

private:
  vec4 color;
  int nb_cell;
};

}
