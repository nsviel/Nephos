#pragma once

#include <Element/src/Base/Glyph.h>
#include <Element/src/Glyph/Grid/Structure.h>


namespace dat::glyph::grid{

class Axis : public dat::base::Glyph, public dat::glyph::grid::Structure
{
public:
  //Constructor / Destructor
  Axis();
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
