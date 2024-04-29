#pragma once

#include <Glyph/Control/Glyph.h>

namespace gly::element::grid{class Mesh;}
namespace gly::element::grid{class Axis;}
namespace gly::element::grid{class Plane;}


namespace gly::element::grid{

class Grid : public utl::entity::Glyph
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
  void set_visibility(bool value);

private:
  gly::element::grid::Mesh* mesh;
  gly::element::grid::Axis* axis;
  gly::element::grid::Plane* plane;

  int nb_cell;
};

}
