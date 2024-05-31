#pragma once

#include <Data/src/Glyph/Grid/Grid.h>


namespace dat::glyph::grid{

class Axis : public dat::glyph::grid::Grid
{
public:
  //Constructor / Destructor
  Axis(eng::Node* node_engine);
  ~Axis();

public:
  //Main function
  void create();

  //Subfunction
  void construct(int nb_cell);

private:
  glm::vec4 color;
};

}
