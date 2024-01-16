#pragma once

#include <Engine/Base/Entity/Glyph.h>


namespace glyph::grid{

class Plane : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Plane(Engine* engine);
  ~Plane();

public:
  //Main function
  void create();
  void update_glyph(int nb_cell);

private:
};

}
