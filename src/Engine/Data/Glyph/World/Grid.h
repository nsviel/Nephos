#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::world{

class Grid : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  //Main function
  eng::structure::Object* create();
  void update();

private:
  int nb_cell;
};

}
