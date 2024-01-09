#pragma once

#include <Engine/Base/Base_glyph.h>
#include <Engine/Data/Glyph/Grid/Namespace.h>

namespace glyph::grid{


class Grid : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  //Main function
  void create();
  void update();
  void insert_object_from_glyph(eng::data::Glyph& glyph);

private:
  glyph::grid::Mesh mesh;
  glyph::grid::Axis axis;
  glyph::grid::Plane plane;

  int nb_cell;
};

}
