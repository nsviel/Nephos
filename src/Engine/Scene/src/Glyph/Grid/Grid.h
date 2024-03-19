#pragma once

#include <Utility/Base/Entity/Glyph.h>

namespace glyph::grid{class Mesh;}
namespace glyph::grid{class Axis;}
namespace glyph::grid{class Plane;}


namespace glyph::grid{

class Grid : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Grid(eng::Node* node_engine);
  ~Grid();

public:
  //Main function
  void create();
  void update_glyph();

private:
  glyph::grid::Mesh* mesh;
  glyph::grid::Axis* axis;
  glyph::grid::Plane* plane;

  int nb_cell;
};

}
