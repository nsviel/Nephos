#pragma once

#include <Glyph/Control/Glyph.h>


namespace gly::element::grid{

class Axis : public utl::entity::Glyph
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
  vec4 color;
};

}