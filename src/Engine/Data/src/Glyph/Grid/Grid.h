#pragma once

#include <Data/src/Base/Glyph.h>

namespace dat::glyph::grid{class Mesh;}
namespace dat::glyph::grid{class Axis;}
namespace dat::glyph::grid{class Plane;}


namespace dat::glyph::grid{

class Grid : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Grid(eng::Node* node_engine);
  ~Grid();

public:
  //Main function
  void create();
  void construct();
  void update_data();
  void update_pose();
  void visibility(bool value);

private:
  dat::glyph::grid::Mesh* mesh;
  dat::glyph::grid::Axis* axis;
  dat::glyph::grid::Plane* plane;

  int nb_cell;
};

}
