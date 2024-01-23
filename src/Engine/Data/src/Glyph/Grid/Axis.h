#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::grid{

class Axis : public entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(Engine* engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_glyph(int nb_cell);

private:
  vec4 color;
};

}
