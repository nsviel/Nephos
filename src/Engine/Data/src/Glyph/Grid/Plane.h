#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::grid{

class Plane : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Plane(eng::Node* engine);
  ~Plane();

public:
  //Main function
  void create();
  void update_glyph(int nb_cell);

private:
};

}
