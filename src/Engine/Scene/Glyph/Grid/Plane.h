#pragma once

#include <Engine/Entity/Base_glyph.h>


namespace glyph::grid{

class Plane : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Plane();
  ~Plane();

public:
  //Main function
  void create();
  void update_glyph(int nb_cell);

private:
};

}
