#pragma once

#include <Engine/Base/Entity/Glyph.h>


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
  void update_glyph(int nb_cell);

private:
  vec4 color;
};

}
