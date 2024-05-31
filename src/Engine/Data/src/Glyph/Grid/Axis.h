#pragma once

#include <Data/src/Base/Glyph.h>


namespace dat::glyph::grid{

class Axis : public dat::base::Glyph
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
