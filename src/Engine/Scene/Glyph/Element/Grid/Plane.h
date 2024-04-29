#pragma once

#include <Glyph/Control/Glyph.h>


namespace gly::element::grid{

class Plane : public utl::entity::Glyph
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
