#pragma once

#include <Data/src/Base/Glyph.h>
#include <Data/src/Glyph/Grid/Structure.h>


namespace dat::glyph::grid{

class Plane : public dat::base::Glyph, public dat::glyph::grid::Structure
{
public:
  //Constructor / Destructor
  Plane();
  ~Plane();

public:
  //Main function
  void create();

  //Subfunction
  void construct(int nb_cell);

private:
};

}
