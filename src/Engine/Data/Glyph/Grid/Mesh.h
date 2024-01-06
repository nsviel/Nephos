#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::grid{

class Mesh : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Mesh();
  ~Mesh();

public:
  //Main function
  void create();
  void update();

private:
  int nb_cell;
};

}
