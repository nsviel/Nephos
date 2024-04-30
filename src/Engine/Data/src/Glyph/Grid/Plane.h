#pragma once

#include <Data/src/Base/Glyph.h>


namespace dat::glyph::grid{

class Plane : public dat::base::Glyph
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
