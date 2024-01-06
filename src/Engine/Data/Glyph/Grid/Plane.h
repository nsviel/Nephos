#pragma once

#include <Engine/Base/Base_glyph.h>


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
  void update();

private:
  int nb_cell;
};

}
