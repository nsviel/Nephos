#pragma once

#include <Data/src/Glyph/Grid/Grid.h>


namespace dat::glyph::grid{

class Plane : public dat::glyph::grid::Grid
{
public:
  //Constructor / Destructor
  Plane(eng::Node* node_engine);
  ~Plane();

public:
  //Main function
  void create();

  //Subfunction
  void construct(int nb_cell);

private:
};

}
