#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::world{

class Grid : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  //Main function
  void create();
  void update();

private:
  int nb_cell;
};

}
